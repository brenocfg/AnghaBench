#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/ * priv; } ;
typedef  TYPE_1__ protocomm_t ;
typedef  int /*<<< orphan*/  httpd_handle_t ;
typedef  int /*<<< orphan*/  esp_err_t ;

/* Variables and functions */
 int /*<<< orphan*/  ESP_ERR_INVALID_ARG ; 
 int /*<<< orphan*/  ESP_OK ; 
 int /*<<< orphan*/  PROTOCOMM_NO_SESSION_ID ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  httpd_stop (int /*<<< orphan*/ ) ; 
 int pc_ext_httpd_handle_provided ; 
 TYPE_1__* pc_httpd ; 
 int /*<<< orphan*/  session_id ; 

esp_err_t protocomm_httpd_stop(protocomm_t *pc)
{
    if ((pc != NULL) && (pc == pc_httpd)) {
        if (!pc_ext_httpd_handle_provided) {
            httpd_handle_t *server_handle = (httpd_handle_t *) pc_httpd->priv;
            httpd_stop(*server_handle);
            free(server_handle);
        } else {
            pc_ext_httpd_handle_provided = false;
        }
        pc_httpd->priv = NULL;
        pc_httpd = NULL;
        session_id = PROTOCOMM_NO_SESSION_ID;
        return ESP_OK;
    }
    return ESP_ERR_INVALID_ARG;
}