#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int max_open_sockets; } ;
struct httpd_data {TYPE_2__* hd_sd; TYPE_1__ config; } ;
typedef  int /*<<< orphan*/  fd_set ;
struct TYPE_4__ {int fd; } ;

/* Variables and functions */
 int /*<<< orphan*/  FD_SET (int,int /*<<< orphan*/ *) ; 

void httpd_sess_set_descriptors(struct httpd_data *hd,
                                fd_set *fdset, int *maxfd)
{
    int i;
    *maxfd = -1;
    for (i = 0; i < hd->config.max_open_sockets; i++) {
        if (hd->hd_sd[i].fd != -1) {
            FD_SET(hd->hd_sd[i].fd, fdset);
            if (hd->hd_sd[i].fd > *maxfd) {
                *maxfd = hd->hd_sd[i].fd;
            }
        }
    }
}