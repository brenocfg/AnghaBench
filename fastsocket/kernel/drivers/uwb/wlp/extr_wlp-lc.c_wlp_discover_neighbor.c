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
struct wlp {int dummy; } ;

/* Variables and functions */
 int wlp_d1d2_exchange (struct wlp*,struct wlp_neighbor_e*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static
int wlp_discover_neighbor(struct wlp *wlp,
			  struct wlp_neighbor_e *neighbor)
{
	return wlp_d1d2_exchange(wlp, neighbor, NULL, NULL);
}