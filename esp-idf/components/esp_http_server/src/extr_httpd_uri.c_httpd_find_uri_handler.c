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
struct TYPE_4__ {int max_uri_handlers; scalar_t__ (* uri_match_fn ) (int /*<<< orphan*/ ,char const*,size_t) ;} ;
struct httpd_data {TYPE_2__** hd_calls; TYPE_1__ config; } ;
struct TYPE_5__ {scalar_t__ method; int /*<<< orphan*/  uri; } ;
typedef  TYPE_2__ httpd_uri_t ;
typedef  scalar_t__ httpd_method_t ;
typedef  scalar_t__ httpd_err_code_t ;

/* Variables and functions */
 int /*<<< orphan*/  ESP_LOGD (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 scalar_t__ HTTPD_404_NOT_FOUND ; 
 scalar_t__ HTTPD_405_METHOD_NOT_ALLOWED ; 
 int /*<<< orphan*/  LOG_FMT (char*) ; 
 int /*<<< orphan*/  TAG ; 
 scalar_t__ httpd_uri_match_simple (int /*<<< orphan*/ ,char const*,size_t) ; 
 scalar_t__ stub1 (int /*<<< orphan*/ ,char const*,size_t) ; 

__attribute__((used)) static httpd_uri_t* httpd_find_uri_handler(struct httpd_data *hd,
                                           const char *uri, size_t uri_len,
                                           httpd_method_t method,
                                           httpd_err_code_t *err)
{
    if (err) {
        *err = HTTPD_404_NOT_FOUND;
    }

    for (int i = 0; i < hd->config.max_uri_handlers; i++) {
        if (!hd->hd_calls[i]) {
            break;
        }
        ESP_LOGD(TAG, LOG_FMT("[%d] = %s"), i, hd->hd_calls[i]->uri);

        /* Check if custom URI matching function is set,
         * else use simple string compare */
        if (hd->config.uri_match_fn ?
            hd->config.uri_match_fn(hd->hd_calls[i]->uri, uri, uri_len) :
            httpd_uri_match_simple(hd->hd_calls[i]->uri, uri, uri_len)) {
            /* URIs match. Now check if method is supported */
            if (hd->hd_calls[i]->method == method) {
                /* Match found! */
                if (err) {
                    /* Unset any error that may
                     * have been set earlier */
                    *err = 0;
                }
                return hd->hd_calls[i];
            }
            /* URI found but method not allowed.
             * If URI is found later then this
             * error must be set to 0 */
            if (err) {
                *err = HTTPD_405_METHOD_NOT_ALLOWED;
            }
        }
    }
    return NULL;
}