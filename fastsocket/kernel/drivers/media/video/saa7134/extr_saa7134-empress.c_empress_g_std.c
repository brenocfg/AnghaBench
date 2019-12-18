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
typedef  int /*<<< orphan*/  v4l2_std_id ;
struct saa7134_dev {TYPE_1__* tvnorm; } ;
struct file {struct saa7134_dev* private_data; } ;
struct TYPE_2__ {int /*<<< orphan*/  id; } ;

/* Variables and functions */

__attribute__((used)) static int empress_g_std(struct file *file, void *priv, v4l2_std_id *id)
{
	struct saa7134_dev *dev = file->private_data;

	*id = dev->tvnorm->id;
	return 0;
}