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
struct wlp_wss {int dummy; } ;
struct wlp_attr_wss_info {int dummy; } ;
struct wlp {int dummy; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  wlp_get_all_wss_info (struct wlp*,struct wlp_attr_wss_info*,int /*<<< orphan*/ *,struct wlp_wss*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static ssize_t wlp_get_wss_info_to_enroll(struct wlp *wlp,
					  struct wlp_attr_wss_info *attr,
					  struct wlp_wss *wss, ssize_t buflen)
{
	return wlp_get_all_wss_info(wlp, attr, NULL, wss, buflen);
}