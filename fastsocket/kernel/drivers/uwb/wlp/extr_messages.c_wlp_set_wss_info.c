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
struct wlp_wss_info {int dummy; } ;
struct wlp_wss {int /*<<< orphan*/  bcast; int /*<<< orphan*/  secure_status; int /*<<< orphan*/  accept_enroll; int /*<<< orphan*/  name; int /*<<< orphan*/  wssid; } ;
struct wlp_attr_wss_info {int /*<<< orphan*/  hdr; void* wss_info; } ;

/* Variables and functions */
 int /*<<< orphan*/  WLP_ATTR_WSS_INFO ; 
 int strlen (int /*<<< orphan*/ ) ; 
 scalar_t__ wlp_set_accept_enrl (void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wlp_set_attr_hdr (int /*<<< orphan*/ *,int /*<<< orphan*/ ,size_t) ; 
 scalar_t__ wlp_set_wss_bcast (void*,int /*<<< orphan*/ *) ; 
 scalar_t__ wlp_set_wss_name (void*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ wlp_set_wss_sec_status (void*,int /*<<< orphan*/ ) ; 
 size_t wlp_set_wssid (void*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static size_t wlp_set_wss_info(struct wlp_attr_wss_info *attr,
			       struct wlp_wss *wss)
{
	size_t datalen;
	void *ptr = attr->wss_info;
	size_t used = sizeof(*attr);

	datalen = sizeof(struct wlp_wss_info) + strlen(wss->name);
	wlp_set_attr_hdr(&attr->hdr, WLP_ATTR_WSS_INFO, datalen);
	used = wlp_set_wssid(ptr, &wss->wssid);
	used += wlp_set_wss_name(ptr + used, wss->name, strlen(wss->name));
	used += wlp_set_accept_enrl(ptr + used, wss->accept_enroll);
	used += wlp_set_wss_sec_status(ptr + used, wss->secure_status);
	used += wlp_set_wss_bcast(ptr + used, &wss->bcast);
	return sizeof(*attr) + used;
}