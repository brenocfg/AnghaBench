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
struct tty_struct {int dummy; } ;
struct hvc_struct {size_t index; int /*<<< orphan*/  kref; int /*<<< orphan*/  lock; int /*<<< orphan*/  tty; } ;

/* Variables and functions */
 size_t MAX_NR_HVC_CONSOLES ; 
 int /*<<< orphan*/  destroy_hvc_struct ; 
 int /*<<< orphan*/  kref_put (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 struct tty_struct* tty_kref_get (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tty_kref_put (struct tty_struct*) ; 
 int /*<<< orphan*/  tty_vhangup (struct tty_struct*) ; 
 int* vtermnos ; 

int hvc_remove(struct hvc_struct *hp)
{
	unsigned long flags;
	struct tty_struct *tty;

	spin_lock_irqsave(&hp->lock, flags);
	tty = tty_kref_get(hp->tty);

	if (hp->index < MAX_NR_HVC_CONSOLES)
		vtermnos[hp->index] = -1;

	/* Don't whack hp->irq because tty_hangup() will need to free the irq. */

	spin_unlock_irqrestore(&hp->lock, flags);

	/*
	 * We 'put' the instance that was grabbed when the kref instance
	 * was initialized using kref_init().  Let the last holder of this
	 * kref cause it to be removed, which will probably be the tty_vhangup
	 * below.
	 */
	kref_put(&hp->kref, destroy_hvc_struct);

	/*
	 * This function call will auto chain call hvc_hangup.
	 */
	if (tty) {
		tty_vhangup(tty);
		tty_kref_put(tty);
	}
	return 0;
}