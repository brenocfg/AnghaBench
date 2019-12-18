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
struct psmouse {struct hgpk_data* private; } ;
struct hgpk_data {int /*<<< orphan*/  recalib_wq; } ;
typedef  size_t ssize_t ;

/* Variables and functions */
 size_t EINVAL ; 
 int /*<<< orphan*/  psmouse_queue_work (struct psmouse*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int strict_strtoul (char const*,int,unsigned long*) ; 

__attribute__((used)) static ssize_t hgpk_trigger_recal(struct psmouse *psmouse, void *data,
				const char *buf, size_t count)
{
	struct hgpk_data *priv = psmouse->private;
	unsigned long value;
	int err;

	err = strict_strtoul(buf, 10, &value);
	if (err || value != 1)
		return -EINVAL;

	/*
	 * We queue work instead of doing recalibration right here
	 * to avoid adding locking to to hgpk_force_recalibrate()
	 * since workqueue provides serialization.
	 */
	psmouse_queue_work(psmouse, &priv->recalib_wq, 0);
	return count;
}