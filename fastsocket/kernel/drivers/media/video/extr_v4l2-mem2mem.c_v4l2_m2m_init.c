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
struct v4l2_m2m_ops {int /*<<< orphan*/  job_abort; int /*<<< orphan*/  device_run; } ;
struct v4l2_m2m_dev {int /*<<< orphan*/  job_spinlock; int /*<<< orphan*/  job_queue; struct v4l2_m2m_ops* m2m_ops; int /*<<< orphan*/ * curr_ctx; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  ENOMEM ; 
 struct v4l2_m2m_dev* ERR_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 struct v4l2_m2m_dev* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

struct v4l2_m2m_dev *v4l2_m2m_init(struct v4l2_m2m_ops *m2m_ops)
{
	struct v4l2_m2m_dev *m2m_dev;

	if (!m2m_ops)
		return ERR_PTR(-EINVAL);

	BUG_ON(!m2m_ops->device_run);
	BUG_ON(!m2m_ops->job_abort);

	m2m_dev = kzalloc(sizeof *m2m_dev, GFP_KERNEL);
	if (!m2m_dev)
		return ERR_PTR(-ENOMEM);

	m2m_dev->curr_ctx = NULL;
	m2m_dev->m2m_ops = m2m_ops;
	INIT_LIST_HEAD(&m2m_dev->job_queue);
	spin_lock_init(&m2m_dev->job_spinlock);

	return m2m_dev;
}