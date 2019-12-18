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
typedef  int /*<<< orphan*/  ushort ;
typedef  int /*<<< orphan*/  PortAddr ;

/* Variables and functions */
 int /*<<< orphan*/  AscSetChipLramAddr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AscSetChipLramData (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void AscWriteLramWord(PortAddr iop_base, ushort addr, ushort word_val)
{
	AscSetChipLramAddr(iop_base, addr);
	AscSetChipLramData(iop_base, word_val);
}