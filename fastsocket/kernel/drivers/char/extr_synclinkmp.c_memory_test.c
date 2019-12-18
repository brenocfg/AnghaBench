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
struct TYPE_3__ {scalar_t__ memory_base; } ;
typedef  TYPE_1__ SLMP_INFO ;

/* Variables and functions */
 unsigned long ARRAY_SIZE (unsigned long*) ; 
 int SCA_MEM_SIZE ; 
 int /*<<< orphan*/  memset (scalar_t__,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static bool memory_test(SLMP_INFO *info)
{
	static unsigned long testval[] = { 0x0, 0x55555555, 0xaaaaaaaa,
		0x66666666, 0x99999999, 0xffffffff, 0x12345678 };
	unsigned long count = ARRAY_SIZE(testval);
	unsigned long i;
	unsigned long limit = SCA_MEM_SIZE/sizeof(unsigned long);
	unsigned long * addr = (unsigned long *)info->memory_base;

	/* Test data lines with test pattern at one location. */

	for ( i = 0 ; i < count ; i++ ) {
		*addr = testval[i];
		if ( *addr != testval[i] )
			return false;
	}

	/* Test address lines with incrementing pattern over */
	/* entire address range. */

	for ( i = 0 ; i < limit ; i++ ) {
		*addr = i * 4;
		addr++;
	}

	addr = (unsigned long *)info->memory_base;

	for ( i = 0 ; i < limit ; i++ ) {
		if ( *addr != i * 4 )
			return false;
		addr++;
	}

	memset( info->memory_base, 0, SCA_MEM_SIZE );
	return true;
}