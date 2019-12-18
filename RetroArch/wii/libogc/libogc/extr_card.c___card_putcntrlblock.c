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
typedef  int /*<<< orphan*/  u32 ;
typedef  void* s32 ;
struct TYPE_3__ {scalar_t__ result; scalar_t__ attached; } ;
typedef  TYPE_1__ card_block ;

/* Variables and functions */
 scalar_t__ CARD_ERROR_BUSY ; 
 int /*<<< orphan*/  _CPU_ISR_Disable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _CPU_ISR_Restore (int /*<<< orphan*/ ) ; 

__attribute__((used)) static s32 __card_putcntrlblock(card_block *card,s32 result)
{
	u32 level;

	_CPU_ISR_Disable(level);
	if(card->attached) card->result = result;
	else if(card->result==CARD_ERROR_BUSY) card->result = result;
	_CPU_ISR_Restore(level);
	return result;
}