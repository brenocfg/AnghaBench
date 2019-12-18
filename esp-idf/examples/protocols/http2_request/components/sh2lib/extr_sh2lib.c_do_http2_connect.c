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
struct sh2lib_handle {int /*<<< orphan*/  http2_sess; } ;
typedef  int /*<<< orphan*/  nghttp2_session_callbacks ;

/* Variables and functions */
 int /*<<< orphan*/  ESP_LOGE (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  NGHTTP2_FLAG_NONE ; 
 int /*<<< orphan*/  TAG ; 
 int /*<<< orphan*/  callback_on_data_chunk_recv ; 
 int /*<<< orphan*/  callback_on_frame_recv ; 
 int /*<<< orphan*/  callback_on_frame_send ; 
 int /*<<< orphan*/  callback_on_header ; 
 int /*<<< orphan*/  callback_on_stream_close ; 
 int /*<<< orphan*/  callback_recv ; 
 int /*<<< orphan*/  callback_send ; 
 int /*<<< orphan*/  nghttp2_session_callbacks_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nghttp2_session_callbacks_new (int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  nghttp2_session_callbacks_set_on_data_chunk_recv_callback (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nghttp2_session_callbacks_set_on_frame_recv_callback (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nghttp2_session_callbacks_set_on_frame_send_callback (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nghttp2_session_callbacks_set_on_header_callback (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nghttp2_session_callbacks_set_on_stream_close_callback (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nghttp2_session_callbacks_set_recv_callback (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nghttp2_session_callbacks_set_send_callback (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int nghttp2_session_client_new (int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct sh2lib_handle*) ; 
 int nghttp2_submit_settings (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int do_http2_connect(struct sh2lib_handle *hd)
{
    int ret;
    nghttp2_session_callbacks *callbacks;
    nghttp2_session_callbacks_new(&callbacks);
    nghttp2_session_callbacks_set_send_callback(callbacks, callback_send);
    nghttp2_session_callbacks_set_recv_callback(callbacks, callback_recv);
    nghttp2_session_callbacks_set_on_frame_send_callback(callbacks, callback_on_frame_send);
    nghttp2_session_callbacks_set_on_frame_recv_callback(callbacks, callback_on_frame_recv);
    nghttp2_session_callbacks_set_on_stream_close_callback(callbacks, callback_on_stream_close);
    nghttp2_session_callbacks_set_on_data_chunk_recv_callback(callbacks, callback_on_data_chunk_recv);
    nghttp2_session_callbacks_set_on_header_callback(callbacks, callback_on_header);
    ret = nghttp2_session_client_new(&hd->http2_sess, callbacks, hd);
    if (ret != 0) {
        ESP_LOGE(TAG, "[sh2-connect] New http2 session failed");
        nghttp2_session_callbacks_del(callbacks);
        return -1;
    }
    nghttp2_session_callbacks_del(callbacks);

    /* Create the SETTINGS frame */
    ret = nghttp2_submit_settings(hd->http2_sess, NGHTTP2_FLAG_NONE, NULL, 0);
    if (ret != 0) {
        ESP_LOGE(TAG, "[sh2-connect] Submit settings failed");
        return -1;
    }
    return 0;
}