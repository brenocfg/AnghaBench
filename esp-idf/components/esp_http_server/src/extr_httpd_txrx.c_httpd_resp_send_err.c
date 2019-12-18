#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct httpd_req_aux {TYPE_1__* sd; } ;
typedef  int /*<<< orphan*/  nodelay ;
struct TYPE_8__ {struct httpd_req_aux* aux; } ;
typedef  TYPE_2__ httpd_req_t ;
typedef  int httpd_err_code_t ;
typedef  int /*<<< orphan*/  esp_err_t ;
struct TYPE_7__ {int /*<<< orphan*/  fd; } ;

/* Variables and functions */
 int /*<<< orphan*/  ESP_ERR_INVALID_STATE ; 
 int /*<<< orphan*/  ESP_LOGE (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ESP_LOGW (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const*,...) ; 
#define  HTTPD_400_BAD_REQUEST 137 
#define  HTTPD_404_NOT_FOUND 136 
#define  HTTPD_405_METHOD_NOT_ALLOWED 135 
#define  HTTPD_408_REQ_TIMEOUT 134 
#define  HTTPD_411_LENGTH_REQUIRED 133 
#define  HTTPD_414_URI_TOO_LONG 132 
#define  HTTPD_431_REQ_HDR_FIELDS_TOO_LARGE 131 
#define  HTTPD_500_INTERNAL_SERVER_ERROR 130 
#define  HTTPD_501_METHOD_NOT_IMPLEMENTED 129 
#define  HTTPD_505_VERSION_NOT_SUPPORTED 128 
 int /*<<< orphan*/  HTTPD_TYPE_TEXT ; 
 int /*<<< orphan*/  IPPROTO_TCP ; 
 int /*<<< orphan*/  LOG_FMT (char*) ; 
 int /*<<< orphan*/  TAG ; 
 int /*<<< orphan*/  TCP_NODELAY ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  httpd_resp_send (TYPE_2__*,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  httpd_resp_set_status (TYPE_2__*,char const*) ; 
 int /*<<< orphan*/  httpd_resp_set_type (TYPE_2__*,int /*<<< orphan*/ ) ; 
 scalar_t__ setsockopt (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int) ; 
 int /*<<< orphan*/  strlen (char const*) ; 

esp_err_t httpd_resp_send_err(httpd_req_t *req, httpd_err_code_t error, const char *usr_msg)
{
    esp_err_t ret;
    const char *msg;
    const char *status;

    switch (error) {
        case HTTPD_501_METHOD_NOT_IMPLEMENTED:
            status = "501 Method Not Implemented";
            msg    = "Request method is not supported by server";
            break;
        case HTTPD_505_VERSION_NOT_SUPPORTED:
            status = "505 Version Not Supported";
            msg    = "HTTP version not supported by server";
            break;
        case HTTPD_400_BAD_REQUEST:
            status = "400 Bad Request";
            msg    = "Server unable to understand request due to invalid syntax";
            break;
        case HTTPD_404_NOT_FOUND:
            status = "404 Not Found";
            msg    = "This URI does not exist";
            break;
        case HTTPD_405_METHOD_NOT_ALLOWED:
            status = "405 Method Not Allowed";
            msg    = "Request method for this URI is not handled by server";
            break;
        case HTTPD_408_REQ_TIMEOUT:
            status = "408 Request Timeout";
            msg    = "Server closed this connection";
            break;
        case HTTPD_414_URI_TOO_LONG:
            status = "414 URI Too Long";
            msg    = "URI is too long for server to interpret";
            break;
        case HTTPD_411_LENGTH_REQUIRED:
            status = "411 Length Required";
            msg    = "Chunked encoding not supported by server";
            break;
        case HTTPD_431_REQ_HDR_FIELDS_TOO_LARGE:
            status = "431 Request Header Fields Too Large";
            msg    = "Header fields are too long for server to interpret";
            break;
        case HTTPD_500_INTERNAL_SERVER_ERROR:
        default:
            status = "500 Internal Server Error";
            msg    = "Server has encountered an unexpected error";
    }

    /* If user has provided custom message, override default message */
    msg = usr_msg ? usr_msg : msg;
    ESP_LOGW(TAG, LOG_FMT("%s - %s"), status, msg);

    /* Set error code in HTTP response */
    httpd_resp_set_status(req, status);
    httpd_resp_set_type(req, HTTPD_TYPE_TEXT);

#ifdef CONFIG_HTTPD_ERR_RESP_NO_DELAY
    /* Use TCP_NODELAY option to force socket to send data in buffer
     * This ensures that the error message is sent before the socket
     * is closed */
    struct httpd_req_aux *ra = req->aux;
    int nodelay = 1;
    if (setsockopt(ra->sd->fd, IPPROTO_TCP, TCP_NODELAY, &nodelay, sizeof(nodelay)) < 0) {
        /* If failed to turn on TCP_NODELAY, throw warning and continue */
        ESP_LOGW(TAG, LOG_FMT("error calling setsockopt : %d"), errno);
        nodelay = 0;
    }
#endif

    /* Send HTTP error message */
    ret = httpd_resp_send(req, msg, strlen(msg));

#ifdef CONFIG_HTTPD_ERR_RESP_NO_DELAY
    /* If TCP_NODELAY was set successfully above, time to disable it */
    if (nodelay == 1) {
        nodelay = 0;
        if (setsockopt(ra->sd->fd, IPPROTO_TCP, TCP_NODELAY, &nodelay, sizeof(nodelay)) < 0) {
            /* If failed to turn off TCP_NODELAY, throw error and
             * return failure to signal for socket closure */
            ESP_LOGE(TAG, LOG_FMT("error calling setsockopt : %d"), errno);
            return ESP_ERR_INVALID_STATE;
        }
    }
#endif

    return ret;
}