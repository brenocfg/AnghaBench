#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct sockaddr {int dummy; } ;
typedef  int /*<<< orphan*/  hostname ;
typedef  int /*<<< orphan*/  buf ;
struct TYPE_6__ {TYPE_2__* priv_data; } ;
typedef  TYPE_1__ URLContext ;
struct TYPE_7__ {scalar_t__ dest_addr_len; int is_connected; int /*<<< orphan*/  dest_addr; int /*<<< orphan*/  udp_fd; int /*<<< orphan*/  is_multicast; } ;
typedef  TYPE_2__ UDPContext ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int /*<<< orphan*/  EIO ; 
 scalar_t__ av_find_info_tag (char*,int,char*,char const*) ; 
 int /*<<< orphan*/  av_url_split (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int,int*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char const*) ; 
 scalar_t__ connect (int /*<<< orphan*/ ,struct sockaddr*,scalar_t__) ; 
 int /*<<< orphan*/  ff_is_multicast_address (struct sockaddr*) ; 
 int /*<<< orphan*/  ff_log_net_error (TYPE_1__*,int /*<<< orphan*/ ,char*) ; 
 char* strchr (char const*,char) ; 
 int strtol (char*,int /*<<< orphan*/ *,int) ; 
 scalar_t__ udp_set_url (TYPE_1__*,int /*<<< orphan*/ *,char*,int) ; 

int ff_udp_set_remote_url(URLContext *h, const char *uri)
{
    UDPContext *s = h->priv_data;
    char hostname[256], buf[10];
    int port;
    const char *p;

    av_url_split(NULL, 0, NULL, 0, hostname, sizeof(hostname), &port, NULL, 0, uri);

    /* set the destination address */
    s->dest_addr_len = udp_set_url(h, &s->dest_addr, hostname, port);
    if (s->dest_addr_len < 0) {
        return AVERROR(EIO);
    }
    s->is_multicast = ff_is_multicast_address((struct sockaddr*) &s->dest_addr);
    p = strchr(uri, '?');
    if (p) {
        if (av_find_info_tag(buf, sizeof(buf), "connect", p)) {
            int was_connected = s->is_connected;
            s->is_connected = strtol(buf, NULL, 10);
            if (s->is_connected && !was_connected) {
                if (connect(s->udp_fd, (struct sockaddr *) &s->dest_addr,
                            s->dest_addr_len)) {
                    s->is_connected = 0;
                    ff_log_net_error(h, AV_LOG_ERROR, "connect");
                    return AVERROR(EIO);
                }
            }
        }
    }

    return 0;
}