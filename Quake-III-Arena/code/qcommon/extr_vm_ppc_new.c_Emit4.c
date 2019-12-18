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
 int* buf ; 
 size_t compiledOfs ; 
 int pass ; 
 int /*<<< orphan*/  printf (char*,int*,char*,int) ; 

__attribute__((used)) static void Emit4( char *opname, int i ) {
	#if DEBUG_VM
	if(pass == 1)
		printf("\t\t\t%p %s\t%08lx\n",&buf[compiledOfs],opname,i&0x3ffffff);
	#endif
	buf[ compiledOfs ] = i;
	compiledOfs++;
}