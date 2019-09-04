#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int sockfd; int /*<<< orphan*/  tout_buf; scalar_t__ tin_buf; scalar_t__ hybi; scalar_t__* cout_buf; int /*<<< orphan*/  cin_buf; } ;
typedef  TYPE_1__ ws_ctx_t ;
struct timeval {int tv_sec; scalar_t__ tv_usec; } ;
typedef  scalar_t__ ssize_t ;
typedef  int /*<<< orphan*/  fd_set ;

/* Variables and functions */
 scalar_t__ BUFSIZE ; 
 int /*<<< orphan*/  DBUFSIZE ; 
 scalar_t__ FD_ISSET (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FD_SET (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FD_ZERO (int /*<<< orphan*/ *) ; 
 scalar_t__ decode_hixie (scalar_t__,unsigned int,int /*<<< orphan*/ ,scalar_t__,unsigned int*,unsigned int*) ; 
 scalar_t__ decode_hybi (scalar_t__,unsigned int,int /*<<< orphan*/ ,scalar_t__,unsigned int*,unsigned int*) ; 
 unsigned int encode_hixie (int /*<<< orphan*/ ,scalar_t__,scalar_t__*,scalar_t__) ; 
 unsigned int encode_hybi (int /*<<< orphan*/ ,scalar_t__,scalar_t__*,scalar_t__,int) ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  handler_emsg (char*,...) ; 
 scalar_t__ pipe_error ; 
 scalar_t__ recv (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 unsigned int select (int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct timeval*) ; 
 scalar_t__ send (int,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strerror (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  traffic (char*) ; 
 scalar_t__ ws_recv (TYPE_1__*,scalar_t__,scalar_t__) ; 
 scalar_t__ ws_send (TYPE_1__*,scalar_t__*,scalar_t__) ; 

void do_proxy(ws_ctx_t *ws_ctx, int target) {
    fd_set rlist, wlist, elist;
    struct timeval tv;
    int i, maxfd, client = ws_ctx->sockfd;
    unsigned int opcode, left, ret;
    unsigned int tout_start, tout_end, cout_start, cout_end;
    unsigned int tin_start, tin_end;
    ssize_t len, bytes;

    tout_start = tout_end = cout_start = cout_end;
    tin_start = tin_end = 0;
    maxfd = client > target ? client+1 : target+1;

    while (1) {
        tv.tv_sec = 1;
        tv.tv_usec = 0;

        FD_ZERO(&rlist);
        FD_ZERO(&wlist);
        FD_ZERO(&elist);

        FD_SET(client, &elist);
        FD_SET(target, &elist);

        if (tout_end == tout_start) {
            // Nothing queued for target, so read from client
            FD_SET(client, &rlist);
        } else {
            // Data queued for target, so write to it
            FD_SET(target, &wlist);
        }
        if (cout_end == cout_start) {
            // Nothing queued for client, so read from target
            FD_SET(target, &rlist);
        } else {
            // Data queued for client, so write to it
            FD_SET(client, &wlist);
        }

        ret = select(maxfd, &rlist, &wlist, &elist, &tv);
        if (pipe_error) { break; }

        if (FD_ISSET(target, &elist)) {
            handler_emsg("target exception\n");
            break;
        }
        if (FD_ISSET(client, &elist)) {
            handler_emsg("client exception\n");
            break;
        }

        if (ret == -1) {
            handler_emsg("select(): %s\n", strerror(errno));
            break;
        } else if (ret == 0) {
            //handler_emsg("select timeout\n");
            continue;
        }

        if (FD_ISSET(target, &wlist)) {
            len = tout_end-tout_start;
            bytes = send(target, ws_ctx->tout_buf + tout_start, len, 0);
            if (pipe_error) { break; }
            if (bytes < 0) {
                handler_emsg("target connection error: %s\n",
                             strerror(errno));
                break;
            }
            tout_start += bytes;
            if (tout_start >= tout_end) {
                tout_start = tout_end = 0;
                traffic(">");
            } else {
                traffic(">.");
            }
        }

        if (FD_ISSET(client, &wlist)) {
            len = cout_end-cout_start;
            bytes = ws_send(ws_ctx, ws_ctx->cout_buf + cout_start, len);
            if (pipe_error) { break; }
            if (len < 3) {
                handler_emsg("len: %d, bytes: %d: %d\n",
                             (int) len, (int) bytes,
                             (int) *(ws_ctx->cout_buf + cout_start));
            }
            cout_start += bytes;
            if (cout_start >= cout_end) {
                cout_start = cout_end = 0;
                traffic("<");
            } else {
                traffic("<.");
            }
        }

        if (FD_ISSET(target, &rlist)) {
            bytes = recv(target, ws_ctx->cin_buf, DBUFSIZE , 0);
            if (pipe_error) { break; }
            if (bytes <= 0) {
                handler_emsg("target closed connection\n");
                break;
            }
            cout_start = 0;
            if (ws_ctx->hybi) {
                cout_end = encode_hybi(ws_ctx->cin_buf, bytes,
                                   ws_ctx->cout_buf, BUFSIZE, 1);
            } else {
                cout_end = encode_hixie(ws_ctx->cin_buf, bytes,
                                    ws_ctx->cout_buf, BUFSIZE);
            }
            /*
            printf("encoded: ");
            for (i=0; i< cout_end; i++) {
                printf("%u,", (unsigned char) *(ws_ctx->cout_buf+i));
            }
            printf("\n");
            */
            if (cout_end < 0) {
                handler_emsg("encoding error\n");
                break;
            }
            traffic("{");
        }

        if (FD_ISSET(client, &rlist)) {
            bytes = ws_recv(ws_ctx, ws_ctx->tin_buf + tin_end, BUFSIZE-1);
            if (pipe_error) { break; }
            if (bytes <= 0) {
                handler_emsg("client closed connection\n");
                break;
            }
            tin_end += bytes;
            /*
            printf("before decode: ");
            for (i=0; i< bytes; i++) {
                printf("%u,", (unsigned char) *(ws_ctx->tin_buf+i));
            }
            printf("\n");
            */
            if (ws_ctx->hybi) {
                len = decode_hybi(ws_ctx->tin_buf + tin_start,
                                  tin_end-tin_start,
                                  ws_ctx->tout_buf, BUFSIZE-1,
                                  &opcode, &left);
            } else {
                len = decode_hixie(ws_ctx->tin_buf + tin_start,
                                   tin_end-tin_start,
                                   ws_ctx->tout_buf, BUFSIZE-1,
                                   &opcode, &left);
            }

            if (opcode == 8) {
                handler_emsg("client sent orderly close frame\n");
                break;
            }

            /*
            printf("decoded: ");
            for (i=0; i< len; i++) {
                printf("%u,", (unsigned char) *(ws_ctx->tout_buf+i));
            }
            printf("\n");
            */
            if (len < 0) {
                handler_emsg("decoding error\n");
                break;
            }
            if (left) {
                tin_start = tin_end - left;
                //printf("partial frame from client");
            } else {
                tin_start = 0;
                tin_end = 0;
            }

            traffic("}");
            tout_start = 0;
            tout_end = len;
        }
    }
}