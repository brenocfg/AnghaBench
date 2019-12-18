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
typedef  int /*<<< orphan*/  u32 ;
struct av7110 {int /*<<< orphan*/  debilock; } ;

/* Variables and functions */
 int /*<<< orphan*/  av7110_debiread (struct av7110*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static inline u32 rdebi(struct av7110 *av7110, u32 config, int addr, u32 val, int count)
{
	unsigned long flags;
	u32 res;

	spin_lock_irqsave(&av7110->debilock, flags);
	res=av7110_debiread(av7110, config, addr, count);
	spin_unlock_irqrestore(&av7110->debilock, flags);
	return res;
}