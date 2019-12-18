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
typedef  int /*<<< orphan*/  httpd_handle_t ;
typedef  int /*<<< orphan*/  esp_err_t ;
struct TYPE_2__ {scalar_t__ priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  ESP_ERR_INVALID_STATE ; 
 int /*<<< orphan*/  ESP_ERR_NO_MEM ; 
 int /*<<< orphan*/  ESP_FAIL ; 
 int /*<<< orphan*/  ESP_LOGD (int /*<<< orphan*/ ,char*,char const*) ; 
 int /*<<< orphan*/  ESP_LOGE (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  ESP_OK ; 
 int /*<<< orphan*/  HTTP_POST ; 
 int /*<<< orphan*/  TAG ; 
 char* calloc (int,scalar_t__) ; 
 int /*<<< orphan*/  esp_err_to_name (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  httpd_unregister_uri_handler (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 TYPE_1__* pc_httpd ; 
 int /*<<< orphan*/  sprintf (char*,char*,char const*) ; 
 scalar_t__ strlen (char const*) ; 

__attribute__((used)) static esp_err_t protocomm_httpd_remove_endpoint(const char *ep_name)
{
    if (pc_httpd == NULL) {
        return ESP_ERR_INVALID_STATE;
    }

    ESP_LOGD(TAG, "Removing endpoint : %s", ep_name);

    /* Construct URI name by prepending '/' to ep_name */
    char* ep_uri = calloc(1, strlen(ep_name) + 2);
    if (!ep_uri) {
        ESP_LOGE(TAG, "Malloc failed for ep uri");
        return ESP_ERR_NO_MEM;
    }
    sprintf(ep_uri, "/%s", ep_name);

    /* Unregister URI handler */
    esp_err_t err;
    httpd_handle_t *server = (httpd_handle_t *) pc_httpd->priv;
    if ((err = httpd_unregister_uri_handler(*server, ep_uri, HTTP_POST)) != ESP_OK) {
        ESP_LOGE(TAG, "Uri handler de-register failed: %s", esp_err_to_name(err));
        free(ep_uri);
        return ESP_FAIL;
    }

    free(ep_uri);
    return ESP_OK;
}