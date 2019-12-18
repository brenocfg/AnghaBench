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
struct saa7134_dev {int /*<<< orphan*/  empress_tsq; } ;
struct file {struct saa7134_dev* private_data; } ;
typedef  enum v4l2_buf_type { ____Placeholder_v4l2_buf_type } v4l2_buf_type ;

/* Variables and functions */
 int videobuf_streamon (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int empress_streamon(struct file *file, void *priv,
					enum v4l2_buf_type type)
{
	struct saa7134_dev *dev = file->private_data;

	return videobuf_streamon(&dev->empress_tsq);
}