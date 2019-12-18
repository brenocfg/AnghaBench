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
struct card_bat {int dummy; } ;
struct TYPE_3__ {struct card_bat* curr_fat; } ;
typedef  TYPE_1__ card_block ;

/* Variables and functions */

__attribute__((used)) static __inline__ struct card_bat* __card_getbatblock(card_block *card)
{
	return card->curr_fat;
}