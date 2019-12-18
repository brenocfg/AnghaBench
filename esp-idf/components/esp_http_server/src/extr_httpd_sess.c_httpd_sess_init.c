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
struct TYPE_4__ {int fd; int /*<<< orphan*/ * ctx; } ;

/* Variables and functions */

void httpd_sess_init(struct httpd_data *hd)
{
    int i;
    for (i = 0; i < hd->config.max_open_sockets; i++) {
        hd->hd_sd[i].fd = -1;
        hd->hd_sd[i].ctx = NULL;
    }
}