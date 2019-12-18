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
struct srmcons_private {int /*<<< orphan*/  timer; int /*<<< orphan*/  lock; int /*<<< orphan*/ * tty; } ;
typedef  int /*<<< orphan*/  DEFINE_SPINLOCK ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  init_timer (int /*<<< orphan*/ *) ; 
 struct srmcons_private* kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int
srmcons_get_private_struct(struct srmcons_private **ps)
{
	static struct srmcons_private *srmconsp = NULL;
	static DEFINE_SPINLOCK(srmconsp_lock);
	unsigned long flags;
	int retval = 0;

	if (srmconsp == NULL) {
		srmconsp = kmalloc(sizeof(*srmconsp), GFP_KERNEL);
		spin_lock_irqsave(&srmconsp_lock, flags);

		if (srmconsp == NULL)
			retval = -ENOMEM;
		else {
			srmconsp->tty = NULL;
			spin_lock_init(&srmconsp->lock);
			init_timer(&srmconsp->timer);
		}

		spin_unlock_irqrestore(&srmconsp_lock, flags);
	}

	*ps = srmconsp;
	return retval;
}