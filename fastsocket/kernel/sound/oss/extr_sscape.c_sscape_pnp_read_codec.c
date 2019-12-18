#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  lock; scalar_t__ codec; } ;
typedef  TYPE_1__ sscape_info ;

/* Variables and functions */
 unsigned char inb (scalar_t__) ; 
 int /*<<< orphan*/  outb (unsigned char,scalar_t__) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static unsigned char sscape_pnp_read_codec(sscape_info* devc, unsigned char reg)
{
	unsigned char res;
	unsigned long flags;

	spin_lock_irqsave(&devc->lock,flags);
	outb( reg, devc -> codec);
	res = inb (devc -> codec + 1);
	spin_unlock_irqrestore(&devc->lock,flags);
	return res;

}