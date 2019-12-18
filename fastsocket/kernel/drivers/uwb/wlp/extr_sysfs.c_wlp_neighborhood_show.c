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
struct wlp {int dummy; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  PAGE_SIZE ; 
 int /*<<< orphan*/  wlp_discover (struct wlp*) ; 
 int /*<<< orphan*/  wlp_wss_neighborhood_print_remove (struct wlp*,char*,int /*<<< orphan*/ ) ; 

ssize_t wlp_neighborhood_show(struct wlp *wlp, char *buf)
{
	wlp_discover(wlp);
	return wlp_wss_neighborhood_print_remove(wlp, buf, PAGE_SIZE);
}