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
struct qdio_q {int nr; int /*<<< orphan*/ * debugfs_q; TYPE_1__* irq_ptr; scalar_t__ is_input_q; } ;
struct ccw_device {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  debugfs_dev; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (int /*<<< orphan*/ *) ; 
 int QDIO_DEBUGFS_NAME_LEN ; 
 int S_IFREG ; 
 int S_IRUGO ; 
 int S_IWUSR ; 
 int /*<<< orphan*/ * debugfs_create_file (char*,int,int /*<<< orphan*/ ,struct qdio_q*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  debugfs_fops ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char*,int) ; 

__attribute__((used)) static void setup_debugfs_entry(struct qdio_q *q, struct ccw_device *cdev)
{
	char name[QDIO_DEBUGFS_NAME_LEN];

	snprintf(name, QDIO_DEBUGFS_NAME_LEN, "%s_%d",
		 q->is_input_q ? "input" : "output",
		 q->nr);
	q->debugfs_q = debugfs_create_file(name, S_IFREG | S_IRUGO | S_IWUSR,
				q->irq_ptr->debugfs_dev, q, &debugfs_fops);
	if (IS_ERR(q->debugfs_q))
		q->debugfs_q = NULL;
}