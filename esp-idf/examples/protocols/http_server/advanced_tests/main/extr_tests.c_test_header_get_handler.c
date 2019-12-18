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
typedef  scalar_t__ esp_err_t ;

/* Variables and functions */
 scalar_t__ ESP_ERR_INVALID_ARG ; 
 scalar_t__ ESP_ERR_NOT_FOUND ; 
 scalar_t__ ESP_ERR_NO_MEM ; 
 scalar_t__ ESP_FAIL ; 
 int /*<<< orphan*/  ESP_LOGE (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  ESP_LOGI (int /*<<< orphan*/ ,char*,...) ; 
 scalar_t__ ESP_OK ; 
 int /*<<< orphan*/  HTTPD_400_BAD_REQUEST ; 
 int /*<<< orphan*/  HTTPD_500_INTERNAL_SERVER_ERROR ; 
 int /*<<< orphan*/  HTTPD_TYPE_TEXT ; 
 int /*<<< orphan*/  TAG ; 
 int /*<<< orphan*/  free (char*) ; 
 int httpd_req_get_hdr_value_len (int /*<<< orphan*/ *,char*) ; 
 scalar_t__ httpd_req_get_hdr_value_str (int /*<<< orphan*/ *,char*,char*,int) ; 
 int /*<<< orphan*/  httpd_resp_send (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  httpd_resp_send_err (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  httpd_resp_set_type (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 char* malloc (int) ; 
 scalar_t__ strcmp (char*,char*) ; 
 int /*<<< orphan*/  strlen (char*) ; 

__attribute__((used)) static esp_err_t test_header_get_handler(httpd_req_t *req)
{
    httpd_resp_set_type(req, HTTPD_TYPE_TEXT);
    int buf_len;
    char *buf;

    buf_len = httpd_req_get_hdr_value_len(req, "Header1");
    if (buf_len > 0) {
        buf = malloc(++buf_len);
        if (!buf) {
            ESP_LOGE(TAG, "Failed to allocate memory of %d bytes!", buf_len);
            httpd_resp_send_err(req, HTTPD_500_INTERNAL_SERVER_ERROR, "Memory allocation failed");
            return ESP_ERR_NO_MEM;
        }
        /* Copy null terminated value string into buffer */
        if (httpd_req_get_hdr_value_str(req, "Header1", buf, buf_len) == ESP_OK) {
            ESP_LOGI(TAG, "Header1 content: %s", buf);
            if (strcmp("Value1", buf) != 0) {
                httpd_resp_send_err(req, HTTPD_400_BAD_REQUEST, "Wrong value of Header1 received");
                free(buf);
                return ESP_ERR_INVALID_ARG;
            } else {
                ESP_LOGI(TAG, "Expected value and received value matched for Header1");
            }
        } else {
            ESP_LOGE(TAG, "Error in getting value of Header1");
            httpd_resp_send_err(req, HTTPD_400_BAD_REQUEST, "Error in getting value of Header1");
            free(buf);
            return ESP_FAIL;
        }
        free(buf);
    } else {
        ESP_LOGE(TAG, "Header1 not found");
        httpd_resp_send_err(req, HTTPD_400_BAD_REQUEST, "Header1 not found");
        return ESP_ERR_NOT_FOUND;
    }

    buf_len = httpd_req_get_hdr_value_len(req, "Header3");
    if (buf_len > 0) {
        buf = malloc(++buf_len);
        if (!buf) {
            ESP_LOGE(TAG, "Failed to allocate memory of %d bytes!", buf_len);
            httpd_resp_send_err(req, HTTPD_500_INTERNAL_SERVER_ERROR, "Memory allocation failed");
            return ESP_ERR_NO_MEM;
        }
        /* Copy null terminated value string into buffer */
        if (httpd_req_get_hdr_value_str(req, "Header3", buf, buf_len) == ESP_OK) {
            ESP_LOGI(TAG, "Header3 content: %s", buf);
            if (strcmp("Value3", buf) != 0) {
                httpd_resp_send_err(req, HTTPD_400_BAD_REQUEST, "Wrong value of Header3 received");
                free(buf);
                return ESP_ERR_INVALID_ARG;
            } else {
                ESP_LOGI(TAG, "Expected value and received value matched for Header3");
            }
        } else {
            ESP_LOGE(TAG, "Error in getting value of Header3");
            httpd_resp_send_err(req, HTTPD_400_BAD_REQUEST, "Error in getting value of Header3");
            free(buf);
            return ESP_FAIL;
        }
        free(buf);
    } else {
        ESP_LOGE(TAG, "Header3 not found");
        httpd_resp_send_err(req, HTTPD_400_BAD_REQUEST, "Header3 not found");
        return ESP_ERR_NOT_FOUND;
    }

    buf_len = httpd_req_get_hdr_value_len(req, "Header2");
    buf = malloc(++buf_len);
    if (!buf) {
        ESP_LOGE(TAG, "Failed to allocate memory of %d bytes!", buf_len);
        httpd_resp_send_err(req, HTTPD_500_INTERNAL_SERVER_ERROR, "Memory allocation failed");
        return ESP_ERR_NO_MEM;
    }
    if (httpd_req_get_hdr_value_str(req, "Header2", buf, buf_len) == ESP_OK) {
        ESP_LOGI(TAG, "Header2 content: %s", buf);
        httpd_resp_send(req, buf, strlen(buf));
    } else {
        ESP_LOGE(TAG, "Header2 not found");
        httpd_resp_send_err(req, HTTPD_400_BAD_REQUEST, "Header2 not found");
        return ESP_FAIL;
    }

    return ESP_OK;
}