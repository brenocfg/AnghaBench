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
 int /*<<< orphan*/  AscSetBank (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  AscWriteChipIH (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void AscSetChipIH(PortAddr iop_base, ushort ins_code)
{
	AscSetBank(iop_base, 1);
	AscWriteChipIH(iop_base, ins_code);
	AscSetBank(iop_base, 0);
}