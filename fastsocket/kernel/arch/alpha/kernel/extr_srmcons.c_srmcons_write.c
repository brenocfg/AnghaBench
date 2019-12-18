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

/* Variables and functions */
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  srmcons_callback_lock ; 
 int /*<<< orphan*/  srmcons_do_write (struct tty_struct*,char const*,int) ; 

__attribute__((used)) static int
srmcons_write(struct tty_struct *tty,
	      const unsigned char *buf, int count)
{
	unsigned long flags;

	spin_lock_irqsave(&srmcons_callback_lock, flags);
	srmcons_do_write(tty, (const char *) buf, count);
	spin_unlock_irqrestore(&srmcons_callback_lock, flags);

	return count;
}