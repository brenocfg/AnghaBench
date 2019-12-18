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
struct drm_device {int /*<<< orphan*/  ctx_idr; } ;

/* Variables and functions */
 int /*<<< orphan*/  idr_init (int /*<<< orphan*/ *) ; 

int drm_ctxbitmap_init(struct drm_device * dev)
{
	idr_init(&dev->ctx_idr);
	return 0;
}