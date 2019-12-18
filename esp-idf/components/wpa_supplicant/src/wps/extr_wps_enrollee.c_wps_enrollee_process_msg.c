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
struct wps_parse_attr {scalar_t__* msg_type; } ;
struct wps_data {int dummy; } ;
struct wpabuf {int dummy; } ;
typedef  enum wsc_op_code { ____Placeholder_wsc_op_code } wsc_op_code ;
typedef  enum wps_process_res { ____Placeholder_wps_process_res } wps_process_res ;

/* Variables and functions */
 int /*<<< orphan*/  MSG_DEBUG ; 
 int WPS_FAILURE ; 
 scalar_t__ WPS_WSC_ACK ; 
 scalar_t__ WPS_WSC_NACK ; 
#define  WSC_ACK 132 
#define  WSC_MSG 131 
#define  WSC_NACK 130 
#define  WSC_Start 129 
#define  WSC_UPnP 128 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*,int,...) ; 
 scalar_t__ wpabuf_len (struct wpabuf const*) ; 
 scalar_t__ wps_parse_msg (struct wpabuf const*,struct wps_parse_attr*) ; 
 int wps_process_wsc_ack (struct wps_data*,struct wpabuf const*) ; 
 int wps_process_wsc_msg (struct wps_data*,struct wpabuf const*) ; 
 int wps_process_wsc_nack (struct wps_data*,struct wpabuf const*) ; 
 int wps_process_wsc_start (struct wps_data*,struct wpabuf const*) ; 
 int /*<<< orphan*/  wps_validate_wsc_ack (struct wpabuf const*) ; 
 int /*<<< orphan*/  wps_validate_wsc_nack (struct wpabuf const*) ; 

enum wps_process_res wps_enrollee_process_msg(struct wps_data *wps,
					      enum wsc_op_code op_code,
					      const struct wpabuf *msg)
{

	wpa_printf(MSG_DEBUG,  "WPS: Processing received message (len=%lu "
		   "op_code=%d)",
		   (unsigned long) wpabuf_len(msg), op_code);

	if (op_code == WSC_UPnP) {
		/* Determine the OpCode based on message type attribute */
		struct wps_parse_attr attr;
		if (wps_parse_msg(msg, &attr) == 0 && attr.msg_type) {
			if (*attr.msg_type == WPS_WSC_ACK)
				op_code = WSC_ACK;
			else if (*attr.msg_type == WPS_WSC_NACK)
				op_code = WSC_NACK;
		}
	}

	switch (op_code) {
        case WSC_Start:
                return wps_process_wsc_start(wps, msg);
	case WSC_MSG:
	case WSC_UPnP:
		return wps_process_wsc_msg(wps, msg);
	case WSC_ACK:
		if (wps_validate_wsc_ack(msg) < 0)
			return WPS_FAILURE;
		return wps_process_wsc_ack(wps, msg);
	case WSC_NACK:
		if (wps_validate_wsc_nack(msg) < 0)
			return WPS_FAILURE;
		return wps_process_wsc_nack(wps, msg);
	default:
		wpa_printf(MSG_DEBUG,  "WPS: Unsupported op_code %d", op_code);
		return WPS_FAILURE;
	}
}