#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct http_parser_url {int dummy; } ;
struct httpd_req_aux {struct http_parser_url url_parse_res; } ;
struct httpd_req {scalar_t__ method; scalar_t__ uri; struct httpd_req_aux* aux; } ;
struct TYPE_5__ {char* at; size_t length; } ;
struct TYPE_6__ {int /*<<< orphan*/  error; TYPE_1__ last; struct httpd_req* req; } ;
typedef  TYPE_2__ parser_data_t ;
struct TYPE_7__ {scalar_t__ method; int http_major; int http_minor; int /*<<< orphan*/  http_errno; scalar_t__ data; } ;
typedef  TYPE_3__ http_parser ;
typedef  int /*<<< orphan*/  esp_err_t ;

/* Variables and functions */
 int /*<<< orphan*/  ESP_FAIL ; 
 int /*<<< orphan*/  ESP_LOGD (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  ESP_LOGW (int /*<<< orphan*/ ,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  ESP_OK ; 
 int /*<<< orphan*/  HTTPD_400_BAD_REQUEST ; 
 int /*<<< orphan*/  HTTPD_414_URI_TOO_LONG ; 
 int /*<<< orphan*/  HTTPD_501_METHOD_NOT_IMPLEMENTED ; 
 int /*<<< orphan*/  HTTPD_505_VERSION_NOT_SUPPORTED ; 
 scalar_t__ HTTP_CONNECT ; 
 int /*<<< orphan*/  LOG_FMT (char*) ; 
 int /*<<< orphan*/  TAG ; 
 scalar_t__ http_parser_parse_url (scalar_t__,int /*<<< orphan*/ ,int,struct http_parser_url*) ; 
 int /*<<< orphan*/  http_parser_url_init (struct http_parser_url*) ; 
 int /*<<< orphan*/  strlcpy (char*,char const*,size_t) ; 
 int /*<<< orphan*/  strlen (scalar_t__) ; 

__attribute__((used)) static esp_err_t verify_url (http_parser *parser)
{
    parser_data_t *parser_data  = (parser_data_t *) parser->data;
    struct httpd_req *r         = parser_data->req;
    struct httpd_req_aux *ra    = r->aux;
    struct http_parser_url *res = &ra->url_parse_res;

    /* Get previous values of the parser callback arguments */
    const char *at = parser_data->last.at;
    size_t  length = parser_data->last.length;

    if ((r->method = parser->method) < 0) {
        ESP_LOGW(TAG, LOG_FMT("HTTP Operation not supported"));
        parser_data->error = HTTPD_501_METHOD_NOT_IMPLEMENTED;
        return ESP_FAIL;
    }

    if (sizeof(r->uri) < (length + 1)) {
        ESP_LOGW(TAG, LOG_FMT("URI length (%d) greater than supported (%d)"),
                 length, sizeof(r->uri));
        parser_data->error = HTTPD_414_URI_TOO_LONG;
        return ESP_FAIL;
    }

    /* Keep URI with terminating null character. Note URI string pointed
     * by 'at' is not NULL terminated, therefore use length provided by
     * parser while copying the URI to buffer */
    strlcpy((char *)r->uri, at, (length + 1));
    ESP_LOGD(TAG, LOG_FMT("received URI = %s"), r->uri);

    /* Make sure version is HTTP/1.1 */
    if ((parser->http_major != 1) && (parser->http_minor != 1)) {
        ESP_LOGW(TAG, LOG_FMT("unsupported HTTP version = %d.%d"),
                 parser->http_major, parser->http_minor);
        parser_data->error = HTTPD_505_VERSION_NOT_SUPPORTED;
        return ESP_FAIL;
    }

    /* Parse URL and keep result for later */
    http_parser_url_init(res);
    if (http_parser_parse_url(r->uri, strlen(r->uri),
                              r->method == HTTP_CONNECT, res)) {
        ESP_LOGW(TAG, LOG_FMT("http_parser_parse_url failed with errno = %d"),
                              parser->http_errno);
        parser_data->error = HTTPD_400_BAD_REQUEST;
        return ESP_FAIL;
    }
    return ESP_OK;
}