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
struct wlp_neighbor_e {int dummy; } ;
struct wlp_attr_wss_info {int dummy; } ;
struct wlp {int dummy; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  wlp_get_all_wss_info (struct wlp*,struct wlp_attr_wss_info*,struct wlp_neighbor_e*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static ssize_t wlp_get_wss_info_to_cache(struct wlp *wlp,
					 struct wlp_attr_wss_info *attr,
					 struct wlp_neighbor_e *neighbor,
					 ssize_t buflen)
{
	return wlp_get_all_wss_info(wlp, attr, neighbor, NULL, buflen);
}