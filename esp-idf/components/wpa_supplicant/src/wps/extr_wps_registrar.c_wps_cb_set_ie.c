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
struct wps_registrar {int (* set_ie_cb ) (int /*<<< orphan*/ ,struct wpabuf*,struct wpabuf*) ;int /*<<< orphan*/  cb_ctx; } ;
struct wpabuf {int dummy; } ;

/* Variables and functions */
 int stub1 (int /*<<< orphan*/ ,struct wpabuf*,struct wpabuf*) ; 

__attribute__((used)) static int wps_cb_set_ie(struct wps_registrar *reg, struct wpabuf *beacon_ie,
			 struct wpabuf *probe_resp_ie)
{
	return reg->set_ie_cb(reg->cb_ctx, beacon_ie, probe_resp_ie);
}