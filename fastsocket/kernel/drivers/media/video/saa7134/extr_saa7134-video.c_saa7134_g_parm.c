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
struct v4l2_streamparm {int dummy; } ;
struct file {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static int saa7134_g_parm(struct file *file, void *fh,
				struct v4l2_streamparm *parm)
{
	return 0;
}