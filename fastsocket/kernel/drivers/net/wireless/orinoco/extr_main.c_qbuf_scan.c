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
struct orinoco_scan_data {int len; int type; int /*<<< orphan*/  list; void* buf; } ;
struct orinoco_private {int /*<<< orphan*/  process_scan; int /*<<< orphan*/  scan_lock; int /*<<< orphan*/  scan_list; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_ATOMIC ; 
 struct orinoco_scan_data* kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  schedule_work (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void qbuf_scan(struct orinoco_private *priv, void *buf,
		      int len, int type)
{
	struct orinoco_scan_data *sd;
	unsigned long flags;

	sd = kmalloc(sizeof(*sd), GFP_ATOMIC);
	if (!sd)
		return;

	sd->buf = buf;
	sd->len = len;
	sd->type = type;

	spin_lock_irqsave(&priv->scan_lock, flags);
	list_add_tail(&sd->list, &priv->scan_list);
	spin_unlock_irqrestore(&priv->scan_lock, flags);

	schedule_work(&priv->process_scan);
}