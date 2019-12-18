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
struct v4l2_control {int dummy; } ;
struct saa7134_fh {int /*<<< orphan*/  dev; } ;
struct file {int dummy; } ;

/* Variables and functions */
 int saa7134_s_ctrl_internal (int /*<<< orphan*/ ,struct saa7134_fh*,struct v4l2_control*) ; 

__attribute__((used)) static int saa7134_s_ctrl(struct file *file, void *f, struct v4l2_control *c)
{
	struct saa7134_fh *fh = f;

	return saa7134_s_ctrl_internal(fh->dev, fh, c);
}