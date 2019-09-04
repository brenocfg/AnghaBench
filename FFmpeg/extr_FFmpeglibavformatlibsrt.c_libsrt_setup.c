#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct addrinfo {struct addrinfo* ai_next; int /*<<< orphan*/  ai_addrlen; int /*<<< orphan*/  ai_addr; int /*<<< orphan*/  ai_socktype; int /*<<< orphan*/  ai_family; int /*<<< orphan*/  ai_flags; int /*<<< orphan*/  member_0; } ;
typedef  int /*<<< orphan*/  proto ;
typedef  int /*<<< orphan*/  portstr ;
typedef  int /*<<< orphan*/  path ;
typedef  int /*<<< orphan*/  packet_size ;
typedef  int /*<<< orphan*/  hostname ;
typedef  int /*<<< orphan*/  buf ;
struct TYPE_11__ {int rw_timeout; int max_packet_size; int is_streamed; TYPE_2__* priv_data; } ;
typedef  TYPE_1__ URLContext ;
struct TYPE_12__ {int eid; scalar_t__ rw_timeout; scalar_t__ mode; scalar_t__ recv_buffer_size; scalar_t__ send_buffer_size; int fd; void* listen_timeout; } ;
typedef  TYPE_2__ SRTContext ;

/* Variables and functions */
 int /*<<< orphan*/  AF_UNSPEC ; 
 int /*<<< orphan*/  AI_PASSIVE ; 
 int AVERROR (int /*<<< orphan*/ ) ; 
 int AVERROR_EXIT ; 
 int AVIO_FLAG_WRITE ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  EIO ; 
 int /*<<< orphan*/  SOCK_DGRAM ; 
 int /*<<< orphan*/  SOL_SOCKET ; 
 int /*<<< orphan*/  SRTO_PAYLOADSIZE ; 
 int /*<<< orphan*/  SRTO_UDP_RCVBUF ; 
 int /*<<< orphan*/  SRTO_UDP_SNDBUF ; 
 scalar_t__ SRT_MODE_LISTENER ; 
 scalar_t__ SRT_MODE_RENDEZVOUS ; 
 scalar_t__ av_find_info_tag (char*,int,char*,char const*) ; 
 int /*<<< orphan*/  av_log (TYPE_1__*,int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  av_url_split (char*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int,int*,char*,int,char const*) ; 
 int /*<<< orphan*/  freeaddrinfo (struct addrinfo*) ; 
 int /*<<< orphan*/  gai_strerror (int) ; 
 int getaddrinfo (char*,char*,struct addrinfo*,struct addrinfo**) ; 
 int libsrt_getsockopt (TYPE_1__*,int,int /*<<< orphan*/ ,char*,int*,int*) ; 
 int libsrt_listen (int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*,int) ; 
 int libsrt_listen_connect (int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,TYPE_1__*,int) ; 
 int libsrt_neterrno (TYPE_1__*) ; 
 int libsrt_set_options_post (TYPE_1__*,int) ; 
 int libsrt_set_options_pre (TYPE_1__*,int) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,int) ; 
 int srt_bind (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  srt_close (int) ; 
 int srt_epoll_create () ; 
 int /*<<< orphan*/  srt_setsockopt (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__*,int) ; 
 int srt_socket (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 char* strchr (char const*,char) ; 
 scalar_t__ strcmp (char*,char*) ; 
 void* strtol (char*,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int libsrt_setup(URLContext *h, const char *uri, int flags)
{
    struct addrinfo hints = { 0 }, *ai, *cur_ai;
    int port, fd = -1;
    SRTContext *s = h->priv_data;
    const char *p;
    char buf[256];
    int ret;
    char hostname[1024],proto[1024],path[1024];
    char portstr[10];
    int open_timeout = 5000000;
    int eid;

    eid = srt_epoll_create();
    if (eid < 0)
        return libsrt_neterrno(h);
    s->eid = eid;

    av_url_split(proto, sizeof(proto), NULL, 0, hostname, sizeof(hostname),
        &port, path, sizeof(path), uri);
    if (strcmp(proto, "srt"))
        return AVERROR(EINVAL);
    if (port <= 0 || port >= 65536) {
        av_log(h, AV_LOG_ERROR, "Port missing in uri\n");
        return AVERROR(EINVAL);
    }
    p = strchr(uri, '?');
    if (p) {
        if (av_find_info_tag(buf, sizeof(buf), "timeout", p)) {
            s->rw_timeout = strtol(buf, NULL, 10);
        }
        if (av_find_info_tag(buf, sizeof(buf), "listen_timeout", p)) {
            s->listen_timeout = strtol(buf, NULL, 10);
        }
    }
    if (s->rw_timeout >= 0) {
        open_timeout = h->rw_timeout = s->rw_timeout;
    }
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_DGRAM;
    snprintf(portstr, sizeof(portstr), "%d", port);
    if (s->mode == SRT_MODE_LISTENER)
        hints.ai_flags |= AI_PASSIVE;
    ret = getaddrinfo(hostname[0] ? hostname : NULL, portstr, &hints, &ai);
    if (ret) {
        av_log(h, AV_LOG_ERROR,
               "Failed to resolve hostname %s: %s\n",
               hostname, gai_strerror(ret));
        return AVERROR(EIO);
    }

    cur_ai = ai;

 restart:

    fd = srt_socket(cur_ai->ai_family, cur_ai->ai_socktype, 0);
    if (fd < 0) {
        ret = libsrt_neterrno(h);
        goto fail;
    }

    if ((ret = libsrt_set_options_pre(h, fd)) < 0) {
        goto fail;
    }

    /* Set the socket's send or receive buffer sizes, if specified.
       If unspecified or setting fails, system default is used. */
    if (s->recv_buffer_size > 0) {
        srt_setsockopt(fd, SOL_SOCKET, SRTO_UDP_RCVBUF, &s->recv_buffer_size, sizeof (s->recv_buffer_size));
    }
    if (s->send_buffer_size > 0) {
        srt_setsockopt(fd, SOL_SOCKET, SRTO_UDP_SNDBUF, &s->send_buffer_size, sizeof (s->send_buffer_size));
    }
    if (s->mode == SRT_MODE_LISTENER) {
        // multi-client
        if ((ret = libsrt_listen(s->eid, fd, cur_ai->ai_addr, cur_ai->ai_addrlen, h, open_timeout / 1000)) < 0)
            goto fail1;
        fd = ret;
    } else {
        if (s->mode == SRT_MODE_RENDEZVOUS) {
            ret = srt_bind(fd, cur_ai->ai_addr, cur_ai->ai_addrlen);
            if (ret)
                goto fail1;
        }

        if ((ret = libsrt_listen_connect(s->eid, fd, cur_ai->ai_addr, cur_ai->ai_addrlen,
                                          open_timeout / 1000, h, !!cur_ai->ai_next)) < 0) {
            if (ret == AVERROR_EXIT)
                goto fail1;
            else
                goto fail;
        }
    }
    if ((ret = libsrt_set_options_post(h, fd)) < 0) {
        goto fail;
    }

    if (flags & AVIO_FLAG_WRITE) {
        int packet_size = 0;
        int optlen = sizeof(packet_size);
        ret = libsrt_getsockopt(h, fd, SRTO_PAYLOADSIZE, "SRTO_PAYLOADSIZE", &packet_size, &optlen);
        if (ret < 0)
            goto fail1;
        if (packet_size > 0)
            h->max_packet_size = packet_size;
    }

    h->is_streamed = 1;
    s->fd = fd;

    freeaddrinfo(ai);
    return 0;

 fail:
    if (cur_ai->ai_next) {
        /* Retry with the next sockaddr */
        cur_ai = cur_ai->ai_next;
        if (fd >= 0)
            srt_close(fd);
        ret = 0;
        goto restart;
    }
 fail1:
    if (fd >= 0)
        srt_close(fd);
    freeaddrinfo(ai);
    return ret;
}