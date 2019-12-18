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
struct omapfb_color_key {int dummy; } ;
struct TYPE_2__ {struct omapfb_color_key color_key; } ;

/* Variables and functions */
 TYPE_1__ dispc ; 

__attribute__((used)) static int omap_dispc_get_color_key(struct omapfb_color_key *ck)
{
	*ck = dispc.color_key;
	return 0;
}