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
typedef  int ushort ;
typedef  int /*<<< orphan*/  PortAddr ;
typedef  long ASC_DCNT ;

/* Variables and functions */
 scalar_t__ AscReadLramWord (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static ASC_DCNT AscMemSumLramWord(PortAddr iop_base, ushort s_addr, int words)
{
	ASC_DCNT sum;
	int i;

	sum = 0L;
	for (i = 0; i < words; i++, s_addr += 2) {
		sum += AscReadLramWord(iop_base, s_addr);
	}
	return (sum);
}