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
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;
struct nouveau_crtc {int /*<<< orphan*/  index; TYPE_1__ base; } ;

/* Variables and functions */
 int /*<<< orphan*/  nv_show_cursor (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
nv04_cursor_show(struct nouveau_crtc *nv_crtc, bool update)
{
	nv_show_cursor(nv_crtc->base.dev, nv_crtc->index, true);
}