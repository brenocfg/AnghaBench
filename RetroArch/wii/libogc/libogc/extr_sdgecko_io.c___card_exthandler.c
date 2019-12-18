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
typedef  size_t s32 ;

/* Variables and functions */
 int /*<<< orphan*/  EXI_Unlock (size_t) ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/ * _ioCardInserted ; 
 int /*<<< orphan*/  sdgecko_doUnmount (size_t) ; 
 int /*<<< orphan*/  sdgecko_ejectedCB (size_t) ; 

__attribute__((used)) static s32 __card_exthandler(s32 chn,s32 dev)
{
	_ioCardInserted[chn] = FALSE;
	sdgecko_doUnmount(chn);
	sdgecko_ejectedCB(chn);
	EXI_Unlock(chn);
	return 1;
}