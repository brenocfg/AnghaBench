#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int msg; void* error_indication; void* config_error; } ;
union wps_event_data {TYPE_1__ fail; } ;
typedef  void* u16 ;
struct wps_context {int /*<<< orphan*/  cb_ctx; int /*<<< orphan*/  (* event_cb ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,union wps_event_data*) ;} ;
typedef  enum wps_msg_type { ____Placeholder_wps_msg_type } wps_msg_type ;

/* Variables and functions */
 int /*<<< orphan*/  WPS_EV_FAIL ; 
 int /*<<< orphan*/  os_free (union wps_event_data*) ; 
 int /*<<< orphan*/  os_memset (union wps_event_data*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ os_zalloc (int) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,union wps_event_data*) ; 

void wps_fail_event(struct wps_context *wps, enum wps_msg_type msg,
		    u16 config_error, u16 error_indication)
{
	union wps_event_data *data;

        data = (union wps_event_data *)os_zalloc(sizeof(union wps_event_data));
	if (data == NULL)
		return;

	if (wps->event_cb == NULL) {
		os_free(data);
		return;
	}

	os_memset(data, 0, sizeof(union wps_event_data));
	data->fail.msg = msg;
	data->fail.config_error = config_error;
	data->fail.error_indication = error_indication;
	wps->event_cb(wps->cb_ctx, WPS_EV_FAIL, data);
	os_free(data);
}