#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct httpd_req_aux {TYPE_1__* sd; } ;
struct TYPE_5__ {struct httpd_req_aux* aux; } ;
typedef  TYPE_2__ httpd_req_t ;
typedef  int /*<<< orphan*/  esp_err_t ;
struct TYPE_4__ {int (* send_fn ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const*,size_t,int /*<<< orphan*/ ) ;int /*<<< orphan*/  fd; int /*<<< orphan*/  handle; } ;

/* Variables and functions */
 int /*<<< orphan*/  ESP_FAIL ; 
 int /*<<< orphan*/  ESP_LOGD (int /*<<< orphan*/ ,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  ESP_OK ; 
 int /*<<< orphan*/  LOG_FMT (char*) ; 
 int /*<<< orphan*/  TAG ; 
 int stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const*,size_t,int /*<<< orphan*/ ) ; 

__attribute__((used)) static esp_err_t httpd_send_all(httpd_req_t *r, const char *buf, size_t buf_len)
{
    struct httpd_req_aux *ra = r->aux;
    int ret;

    while (buf_len > 0) {
        ret = ra->sd->send_fn(ra->sd->handle, ra->sd->fd, buf, buf_len, 0);
        if (ret < 0) {
            ESP_LOGD(TAG, LOG_FMT("error in send_fn"));
            return ESP_FAIL;
        }
        ESP_LOGD(TAG, LOG_FMT("sent = %d"), ret);
        buf     += ret;
        buf_len -= ret;
    }
    return ESP_OK;
}