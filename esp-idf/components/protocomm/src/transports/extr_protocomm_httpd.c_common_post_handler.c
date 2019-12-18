#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  char uint8_t ;
typedef  int /*<<< orphan*/  ssize_t ;
struct TYPE_10__ {scalar_t__ content_len; char* uri; } ;
typedef  TYPE_2__ httpd_req_t ;
typedef  scalar_t__ esp_err_t ;
struct TYPE_11__ {int /*<<< orphan*/  sec_inst; TYPE_1__* sec; } ;
struct TYPE_9__ {scalar_t__ (* close_transport_session ) (int /*<<< orphan*/ ,int) ;scalar_t__ (* new_transport_session ) (int /*<<< orphan*/ ,int) ;} ;

/* Variables and functions */
 scalar_t__ ESP_ERR_NO_MEM ; 
 scalar_t__ ESP_FAIL ; 
 int /*<<< orphan*/  ESP_LOGD (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  ESP_LOGE (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  ESP_LOGW (int /*<<< orphan*/ ,char*,int) ; 
 scalar_t__ ESP_OK ; 
 scalar_t__ MAX_REQ_BODY_LEN ; 
 int PROTOCOMM_NO_SESSION_ID ; 
 int /*<<< orphan*/  TAG ; 
 int /*<<< orphan*/  free (char*) ; 
 scalar_t__ httpd_req_recv (TYPE_2__*,char*,size_t) ; 
 int httpd_req_to_sockfd (TYPE_2__*) ; 
 scalar_t__ httpd_resp_send (TYPE_2__*,char*,int /*<<< orphan*/ ) ; 
 scalar_t__ malloc (scalar_t__) ; 
 TYPE_3__* pc_httpd ; 
 scalar_t__ protocomm_req_handle (TYPE_3__*,char const*,int,char*,size_t,char**,int /*<<< orphan*/ *) ; 
 int session_id ; 
 scalar_t__ stub1 (int /*<<< orphan*/ ,int) ; 
 scalar_t__ stub2 (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static esp_err_t common_post_handler(httpd_req_t *req)
{
    esp_err_t ret;
    uint8_t *outbuf = NULL;
    char *req_body = NULL;
    const char *ep_name = NULL;
    ssize_t outlen;

    int cur_session_id = httpd_req_to_sockfd(req);

    if (cur_session_id != session_id) {
        /* Initialize new security session */
        if (session_id != PROTOCOMM_NO_SESSION_ID) {
            ESP_LOGD(TAG, "Closing session with ID: %d", session_id);
            /* Presently HTTP server doesn't support callback on socket closure so
             * previous session can only be closed when new session is requested */
            if (pc_httpd->sec && pc_httpd->sec->close_transport_session) {
                ret = pc_httpd->sec->close_transport_session(pc_httpd->sec_inst, session_id);
                if (ret != ESP_OK) {
                    ESP_LOGW(TAG, "Error closing session with ID: %d", session_id);
                }
            }
            session_id = PROTOCOMM_NO_SESSION_ID;
        }
        if (pc_httpd->sec && pc_httpd->sec->new_transport_session) {
            ret = pc_httpd->sec->new_transport_session(pc_httpd->sec_inst, cur_session_id);
            if (ret != ESP_OK) {
                ESP_LOGE(TAG, "Failed to launch new session with ID: %d", cur_session_id);
                ret = ESP_FAIL;
                goto out;
            }
        }
        session_id = cur_session_id;
        ESP_LOGD(TAG, "New session with ID: %d", cur_session_id);
    }

    if (req->content_len <= 0) {
        ESP_LOGE(TAG, "Content length not found");
        ret = ESP_FAIL;
        goto out;
    } else if (req->content_len > MAX_REQ_BODY_LEN) {
        ESP_LOGE(TAG, "Request content length should be less than 4kb");
        ret = ESP_FAIL;
        goto out;
    }

    req_body = (char *) malloc(req->content_len);
    if (!req_body) {
        ESP_LOGE(TAG, "Unable to allocate for request length %d", req->content_len);
        ret = ESP_ERR_NO_MEM;
        goto out;
    }

    size_t recv_size = 0;
    while (recv_size < req->content_len) {
        ret = httpd_req_recv(req, req_body + recv_size, req->content_len - recv_size);
        if (ret < 0) {
            ret = ESP_FAIL;
            goto out;
        }
        recv_size += ret;
    }

    /* Extract the endpoint name from URI string of type "/ep_name" */
    ep_name = req->uri + 1;

    ret = protocomm_req_handle(pc_httpd, ep_name, session_id,
                               (uint8_t *)req_body, recv_size, &outbuf, &outlen);

    if (ret != ESP_OK) {
        ESP_LOGE(TAG, "Data handler failed");
        ret = ESP_FAIL;
        goto out;
    }

    ret = httpd_resp_send(req, (char *)outbuf, outlen);
    if (ret != ESP_OK) {
        ESP_LOGE(TAG, "HTTP send failed");
        ret = ESP_FAIL;
        goto out;
    }
    ret = ESP_OK;
out:
    if (req_body) {
        free(req_body);
    }
    if (outbuf) {
        free(outbuf);
    }
    return ret;
}