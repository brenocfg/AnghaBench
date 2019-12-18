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
struct vc_data {scalar_t__ vc_origin; scalar_t__ vc_visible_origin; } ;

/* Variables and functions */
 int /*<<< orphan*/  vgacon_scrolldelta (struct vc_data*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void vgacon_restore_screen(struct vc_data *c)
{
	if (c->vc_origin != c->vc_visible_origin)
		vgacon_scrolldelta(c, 0);
}