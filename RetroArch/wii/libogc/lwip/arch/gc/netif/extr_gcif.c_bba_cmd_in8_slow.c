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
typedef  int /*<<< orphan*/  val ;
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u32 ;

/* Variables and functions */
 int /*<<< orphan*/  bba_cmd_insnosel (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  bba_deselect () ; 
 int /*<<< orphan*/  bba_select () ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static inline u8 bba_cmd_in8_slow(u32 reg)
{
	u8 val;
	bba_select();
	bba_cmd_insnosel(reg,&val,sizeof(val));
	udelay(200);			//usleep doesn't work on this amount, decrementer is based on 10ms, wait is 200us
	bba_deselect();
	return val;
}