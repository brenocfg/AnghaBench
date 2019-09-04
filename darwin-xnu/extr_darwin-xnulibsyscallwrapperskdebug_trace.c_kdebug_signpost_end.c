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
typedef  int uint32_t ;

/* Variables and functions */
 int DBG_FUNC_END ; 
 int KDBG_CODE_OFFSET ; 
 int kdebug_signpost_internal (int,uintptr_t,uintptr_t,uintptr_t,uintptr_t) ; 

int
kdebug_signpost_end(uint32_t code, uintptr_t arg1, uintptr_t arg2, uintptr_t arg3, uintptr_t arg4)
{
	return kdebug_signpost_internal((code << KDBG_CODE_OFFSET) | DBG_FUNC_END, arg1, arg2, arg3, arg4);
}