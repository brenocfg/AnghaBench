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
typedef  int /*<<< orphan*/  protocomm_req_handler_t ;
struct TYPE_4__ {char* uri; int /*<<< orphan*/ * user_ctx; int /*<<< orphan*/  handler; int /*<<< orphan*/  method; } ;
typedef  TYPE_1__ httpd_uri_t ;
typedef  int /*<<< orphan*/  httpd_handle_t ;
typedef  int /*<<< orphan*/  esp_err_t ;
struct TYPE_5__ {scalar_t__ priv; } ;

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
 int /*<<< orphan*/  common_post_handler ; 
 int /*<<< orphan*/  esp_err_to_name (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  httpd_register_uri_handler (int /*<<< orphan*/ ,TYPE_1__*) ; 
 TYPE_2__* pc_httpd ; 
 int /*<<< orphan*/  sprintf (char*,char*,char const*) ; 
 scalar_t__ strlen (char const*) ; 

__attribute__((used)) static esp_err_t protocomm_httpd_add_endpoint(const char *ep_name,
                                       protocomm_req_handler_t req_handler,
                                       void *priv_data)
{
    if (pc_httpd == NULL) {
        return ESP_ERR_INVALID_STATE;
    }

    ESP_LOGD(TAG, "Adding endpoint : %s", ep_name);

    /* Construct URI name by prepending '/' to ep_name */
    char* ep_uri = calloc(1, strlen(ep_name) + 2);
    if (!ep_uri) {
        ESP_LOGE(TAG, "Malloc failed for ep uri");
        return ESP_ERR_NO_MEM;
    }

    /* Create URI handler structure */
    sprintf(ep_uri, "/%s", ep_name);
    httpd_uri_t config_handler = {
        .uri      = ep_uri,
        .method   = HTTP_POST,
        .handler  = common_post_handler,
        .user_ctx = NULL
    };

    /* Register URI handler */
    esp_err_t err;
    httpd_handle_t *server = (httpd_handle_t *) pc_httpd->priv;
    if ((err = httpd_register_uri_handler(*server, &config_handler)) != ESP_OK) {
        ESP_LOGE(TAG, "Uri handler register failed: %s", esp_err_to_name(err));
        free(ep_uri);
        return ESP_FAIL;
    }

    free(ep_uri);
    return ESP_OK;
}