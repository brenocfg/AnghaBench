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
struct DiskOnChip {int /*<<< orphan*/  virtadr; } ;

/* Variables and functions */
 int /*<<< orphan*/  DOCStatus ; 
 scalar_t__ DoC_is_Millennium (struct DiskOnChip*) ; 
 int /*<<< orphan*/  NOP ; 
 char ReadDOC (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void DoC_Delay(struct DiskOnChip *doc, unsigned short cycles)
{
	volatile char dummy;
	int i;

	for (i = 0; i < cycles; i++) {
		if (DoC_is_Millennium(doc))
			dummy = ReadDOC(doc->virtadr, NOP);
		else
			dummy = ReadDOC(doc->virtadr, DOCStatus);
	}

}