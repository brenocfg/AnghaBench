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
typedef  int u32 ;

/* Variables and functions */
 int __card_rand () ; 
 int /*<<< orphan*/  __card_srand (int) ; 
 int gettick () ; 

__attribute__((used)) static u32 __card_dummylen()
{
	u32 ticks = gettick();
	u32 val = 0,cnt = 0,shift = 1;

	__card_srand(ticks);
	val = (__card_rand()&0x1f)+1;

	do {
		ticks = gettick();
		val = ticks<<shift;
		shift++;
		if(shift>16) shift = 1;
		__card_srand(val);
		val = (__card_rand()&0x1f)+1;
		cnt++;
	}while(val<4 && cnt<10);
	if(val<4) val = 4;

	return val;

}