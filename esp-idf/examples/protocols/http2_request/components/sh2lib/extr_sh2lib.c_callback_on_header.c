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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  nghttp2_session ;
struct TYPE_4__ {int /*<<< orphan*/  stream_id; } ;
struct TYPE_5__ {TYPE_1__ hd; } ;
typedef  TYPE_2__ nghttp2_frame ;

/* Variables and functions */
 int /*<<< orphan*/  ESP_LOGD (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  TAG ; 

__attribute__((used)) static int callback_on_header(nghttp2_session *session, const nghttp2_frame *frame,
                              const uint8_t *name, size_t namelen, const uint8_t *value,
                              size_t valuelen, uint8_t flags, void *user_data)
{
    ESP_LOGD(TAG, "[hdr-recv][sid:%d] %s : %s", frame->hd.stream_id, name, value);
    return 0;
}