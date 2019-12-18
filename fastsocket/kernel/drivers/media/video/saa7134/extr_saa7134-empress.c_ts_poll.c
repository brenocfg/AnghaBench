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
struct poll_table_struct {int dummy; } ;
struct file {struct saa7134_dev* private_data; } ;

/* Variables and functions */
 unsigned int videobuf_poll_stream (struct file*,int /*<<< orphan*/ *,struct poll_table_struct*) ; 

__attribute__((used)) static unsigned int
ts_poll(struct file *file, struct poll_table_struct *wait)
{
	struct saa7134_dev *dev = file->private_data;

	return videobuf_poll_stream(file, &dev->empress_tsq, wait);
}