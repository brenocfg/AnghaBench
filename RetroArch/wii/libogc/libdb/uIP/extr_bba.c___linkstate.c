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
typedef  int u8 ;
typedef  int u32 ;

/* Variables and functions */
 int /*<<< orphan*/  BBA_NWAYS ; 
 int BBA_NWAYS_LS10 ; 
 int BBA_NWAYS_LS100 ; 
 int bba_in8 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static __inline__ u32 __linkstate()
{
	u8 nways = 0;

	nways = bba_in8(BBA_NWAYS);
	if(nways&BBA_NWAYS_LS10 || nways&BBA_NWAYS_LS100) return 1;
	return 0;
}