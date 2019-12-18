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
typedef  int /*<<< orphan*/  sh2lib_frame_data_recv_cb_t ;
typedef  int /*<<< orphan*/  nghttp2_nv ;

/* Variables and functions */
 int /*<<< orphan*/  ESP_LOGE (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  TAG ; 
 int nghttp2_submit_request (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/  const*,size_t,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

int sh2lib_do_get_with_nv(struct sh2lib_handle *hd, const nghttp2_nv *nva, size_t nvlen, sh2lib_frame_data_recv_cb_t recv_cb)
{
    int ret = nghttp2_submit_request(hd->http2_sess, NULL, nva, nvlen, NULL, recv_cb);
    if (ret < 0) {
        ESP_LOGE(TAG, "[sh2-do-get] HEADERS call failed");
        return -1;
    }
    return ret;
}