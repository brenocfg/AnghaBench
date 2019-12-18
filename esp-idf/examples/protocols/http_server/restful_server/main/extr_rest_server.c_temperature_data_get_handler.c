#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  httpd_req_t ;
typedef  int /*<<< orphan*/  esp_err_t ;
typedef  int /*<<< orphan*/  cJSON ;

/* Variables and functions */
 int /*<<< orphan*/  ESP_OK ; 
 int /*<<< orphan*/  cJSON_AddNumberToObject (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/ * cJSON_CreateObject () ; 
 int /*<<< orphan*/  cJSON_Delete (int /*<<< orphan*/ *) ; 
 char* cJSON_Print (int /*<<< orphan*/ *) ; 
 int esp_random () ; 
 int /*<<< orphan*/  free (void*) ; 
 int /*<<< orphan*/  httpd_resp_sendstr (int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/  httpd_resp_set_type (int /*<<< orphan*/ *,char*) ; 

__attribute__((used)) static esp_err_t temperature_data_get_handler(httpd_req_t *req)
{
    httpd_resp_set_type(req, "application/json");
    cJSON *root = cJSON_CreateObject();
    cJSON_AddNumberToObject(root, "raw", esp_random() % 20);
    const char *sys_info = cJSON_Print(root);
    httpd_resp_sendstr(req, sys_info);
    free((void *)sys_info);
    cJSON_Delete(root);
    return ESP_OK;
}