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
typedef  int uint8_t ;
struct TYPE_2__ {int ibf; int wi; int /*<<< orphan*/  ibf_lock; int /*<<< orphan*/  status_io; } ;

/* Variables and functions */
 TYPE_1__ hp_sdc ; 
 int /*<<< orphan*/  sdc_writeb (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  write_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  write_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static inline void hp_sdc_status_out8(uint8_t val)
{
	unsigned long flags;

	write_lock_irqsave(&hp_sdc.ibf_lock, flags);
	hp_sdc.ibf = 1;
	if ((val & 0xf0) == 0xe0)
		hp_sdc.wi = 0xff;
	sdc_writeb(val, hp_sdc.status_io);
	write_unlock_irqrestore(&hp_sdc.ibf_lock, flags);
}