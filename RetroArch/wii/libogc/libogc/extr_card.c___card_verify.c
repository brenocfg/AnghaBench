#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
typedef  int /*<<< orphan*/  s32 ;
struct TYPE_5__ {scalar_t__ curr_fat; scalar_t__ curr_dir; } ;
typedef  TYPE_1__ card_block ;

/* Variables and functions */
 int /*<<< orphan*/  CARD_ERROR_BROKEN ; 
 int /*<<< orphan*/  CARD_ERROR_READY ; 
 scalar_t__ __card_checkdir (TYPE_1__*,int /*<<< orphan*/ *) ; 
 scalar_t__ __card_checkfat (TYPE_1__*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static s32 __card_verify(card_block *card)
{
	u32 ret = 0;

	ret += __card_checkdir(card,NULL);
	ret += __card_checkfat(card,NULL);
	if(ret<=2) {
		if(card->curr_dir && card->curr_fat) return CARD_ERROR_READY;
	}
	return CARD_ERROR_BROKEN;
}