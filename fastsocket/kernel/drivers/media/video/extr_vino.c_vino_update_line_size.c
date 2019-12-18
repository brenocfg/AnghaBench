#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {unsigned int right; unsigned int left; } ;
struct vino_channel_settings {unsigned int decimation; size_t data_format; unsigned int line_size; TYPE_1__ clipping; } ;
struct TYPE_4__ {unsigned int bpp; } ;

/* Variables and functions */
 int /*<<< orphan*/  dprintk (char*,unsigned int,unsigned int,unsigned int) ; 
 TYPE_2__* vino_data_formats ; 

__attribute__((used)) static void vino_update_line_size(struct vino_channel_settings *vcs)
{
	unsigned int w = vcs->clipping.right - vcs->clipping.left;
	unsigned int d = vcs->decimation;
	unsigned int bpp = vino_data_formats[vcs->data_format].bpp;
	unsigned int lsize;

	dprintk("update_line_size(): before: w = %d, d = %d, "
		"line_size = %d\n", w, d, vcs->line_size);

	/* line size must be multiple of 8 bytes */
	lsize = (bpp * (w / d)) & ~7;
	w = (lsize / bpp) * d;

	vcs->clipping.right = vcs->clipping.left + w;
	vcs->line_size = lsize;

	dprintk("update_line_size(): after: w = %d, d = %d, "
		"line_size = %d\n", w, d, vcs->line_size);
}