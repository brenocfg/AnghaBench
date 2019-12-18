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
struct TYPE_3__ {int max_open_sockets; int /*<<< orphan*/  (* close_fn ) (struct httpd_data*,int) ;} ;
struct httpd_data {TYPE_2__* hd_sd; TYPE_1__ config; } ;
struct TYPE_4__ {int fd; int /*<<< orphan*/  (* free_transport_ctx ) (int /*<<< orphan*/ *) ;int /*<<< orphan*/ * transport_ctx; int /*<<< orphan*/  (* free_ctx ) (int /*<<< orphan*/ *) ;int /*<<< orphan*/ * ctx; } ;

/* Variables and functions */
 int /*<<< orphan*/  ESP_LOGD (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  LOG_FMT (char*) ; 
 int /*<<< orphan*/  TAG ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct httpd_data*,int) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub3 (int /*<<< orphan*/ *) ; 

int httpd_sess_delete(struct httpd_data *hd, int fd)
{
    ESP_LOGD(TAG, LOG_FMT("fd = %d"), fd);
    int i;
    int pre_sess_fd = -1;
    for (i = 0; i < hd->config.max_open_sockets; i++) {
        if (hd->hd_sd[i].fd == fd) {
            /* global close handler */
            if (hd->config.close_fn) {
                hd->config.close_fn(hd, fd);
            }

            /* release 'user' context */
            if (hd->hd_sd[i].ctx) {
                if (hd->hd_sd[i].free_ctx) {
                    hd->hd_sd[i].free_ctx(hd->hd_sd[i].ctx);
                } else {
                    free(hd->hd_sd[i].ctx);
                }
                hd->hd_sd[i].ctx = NULL;
                hd->hd_sd[i].free_ctx = NULL;
            }

            /* release 'transport' context */
            if (hd->hd_sd[i].transport_ctx) {
                if (hd->hd_sd[i].free_transport_ctx) {
                    hd->hd_sd[i].free_transport_ctx(hd->hd_sd[i].transport_ctx);
                } else {
                    free(hd->hd_sd[i].transport_ctx);
                }
                hd->hd_sd[i].transport_ctx = NULL;
                hd->hd_sd[i].free_transport_ctx = NULL;
            }

            /* mark session slot as available */
            hd->hd_sd[i].fd = -1;
            break;
        } else if (hd->hd_sd[i].fd != -1) {
            /* Return the fd just preceding the one being
             * deleted so that iterator can continue from
             * the correct fd */
            pre_sess_fd = hd->hd_sd[i].fd;
        }
    }
    return pre_sess_fd;
}