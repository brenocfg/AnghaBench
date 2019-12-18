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

/* Variables and functions */
 scalar_t__ CARDIO_ERROR_NOCARD ; 
 scalar_t__ sdgecko_readStatus (int) ; 

__attribute__((used)) static bool __gcsd_isInserted(int n)
{
	if(sdgecko_readStatus(n) == CARDIO_ERROR_NOCARD)
		return false;
	return true;
}