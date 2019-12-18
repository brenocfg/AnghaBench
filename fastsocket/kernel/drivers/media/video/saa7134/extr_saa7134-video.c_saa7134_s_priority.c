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
struct saa7134_fh {int /*<<< orphan*/  prio; struct saa7134_dev* dev; } ;
struct saa7134_dev {int /*<<< orphan*/  prio; } ;
struct file {int dummy; } ;
typedef  enum v4l2_priority { ____Placeholder_v4l2_priority } v4l2_priority ;

/* Variables and functions */
 int v4l2_prio_change (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int saa7134_s_priority(struct file *file, void *f,
					enum v4l2_priority prio)
{
	struct saa7134_fh *fh = f;
	struct saa7134_dev *dev = fh->dev;

	return v4l2_prio_change(&dev->prio, &fh->prio, prio);
}