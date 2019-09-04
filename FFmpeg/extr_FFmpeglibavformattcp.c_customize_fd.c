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
struct TYPE_2__ {scalar_t__ recv_buffer_size; scalar_t__ send_buffer_size; scalar_t__ tcp_nodelay; scalar_t__ tcp_mss; } ;
typedef  TYPE_1__ TCPContext ;

/* Variables and functions */
 int /*<<< orphan*/  AV_LOG_WARNING ; 
 int /*<<< orphan*/  IPPROTO_TCP ; 
 int /*<<< orphan*/  SOL_SOCKET ; 
 int /*<<< orphan*/  SO_RCVBUF ; 
 int /*<<< orphan*/  SO_SNDBUF ; 
 int /*<<< orphan*/  TCP_MAXSEG ; 
 int /*<<< orphan*/  TCP_NODELAY ; 
 int /*<<< orphan*/  ff_log_net_error (void*,int /*<<< orphan*/ ,char*) ; 
 scalar_t__ setsockopt (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__*,int) ; 

__attribute__((used)) static void customize_fd(void *ctx, int fd)
{
    TCPContext *s = ctx;
    /* Set the socket's send or receive buffer sizes, if specified.
       If unspecified or setting fails, system default is used. */
    if (s->recv_buffer_size > 0) {
        if (setsockopt (fd, SOL_SOCKET, SO_RCVBUF, &s->recv_buffer_size, sizeof (s->recv_buffer_size))) {
            ff_log_net_error(ctx, AV_LOG_WARNING, "setsockopt(SO_RCVBUF)");
        }
    }
    if (s->send_buffer_size > 0) {
        if (setsockopt (fd, SOL_SOCKET, SO_SNDBUF, &s->send_buffer_size, sizeof (s->send_buffer_size))) {
            ff_log_net_error(ctx, AV_LOG_WARNING, "setsockopt(SO_SNDBUF)");
        }
    }
    if (s->tcp_nodelay > 0) {
        if (setsockopt (fd, IPPROTO_TCP, TCP_NODELAY, &s->tcp_nodelay, sizeof (s->tcp_nodelay))) {
            ff_log_net_error(ctx, AV_LOG_WARNING, "setsockopt(TCP_NODELAY)");
        }
    }
#if !HAVE_WINSOCK2_H
    if (s->tcp_mss > 0) {
        if (setsockopt (fd, IPPROTO_TCP, TCP_MAXSEG, &s->tcp_mss, sizeof (s->tcp_mss))) {
            ff_log_net_error(ctx, AV_LOG_WARNING, "setsockopt(TCP_MAXSEG)");
        }
    }
#endif /* !HAVE_WINSOCK2_H */
}