#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  uint32_t ;
struct sh2lib_handle {int dummy; } ;
typedef  int /*<<< orphan*/  ssize_t ;
typedef  int /*<<< orphan*/  (* sh2lib_putpost_data_cb_t ) (struct sh2lib_handle*,char*,size_t,int /*<<< orphan*/ *) ;
typedef  int /*<<< orphan*/  nghttp2_session ;
struct TYPE_3__ {int /*<<< orphan*/  (* ptr ) (struct sh2lib_handle*,char*,size_t,int /*<<< orphan*/ *) ;} ;
typedef  TYPE_1__ nghttp2_data_source ;
typedef  int /*<<< orphan*/  int32_t ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (struct sh2lib_handle*,char*,size_t,int /*<<< orphan*/ *) ; 

ssize_t sh2lib_data_provider_cb(nghttp2_session *session, int32_t stream_id, uint8_t *buf,
                                size_t length, uint32_t *data_flags,
                                nghttp2_data_source *source, void *user_data)
{
    struct sh2lib_handle *h2 = user_data;
    sh2lib_putpost_data_cb_t data_cb = source->ptr;
    return (*data_cb)(h2, (char *)buf, length, data_flags);
}