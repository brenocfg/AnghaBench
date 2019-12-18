#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  dword ;
typedef  int /*<<< orphan*/  diva_trace_ie_t ;
struct TYPE_8__ {int type; } ;
typedef  TYPE_1__ diva_man_var_header_t ;

/* Variables and functions */
 int diva_strace_read_asc (TYPE_1__*,char*) ; 
 int diva_strace_read_asz (TYPE_1__*,char*) ; 
 int diva_strace_read_ie (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int diva_strace_read_int (TYPE_1__*,int*) ; 
 int diva_strace_read_uint (TYPE_1__*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int diva_trace_read_variable (diva_man_var_header_t* pVar,
																		 void* variable) {
	switch (pVar->type) {
		case 0x03: /* MI_ASCIIZ - syting                               */
			return (diva_strace_read_asz  (pVar, (char*)variable));
		case 0x04: /* MI_ASCII  - string                               */
			return (diva_strace_read_asc  (pVar, (char*)variable));
		case 0x05: /* MI_NUMBER - counted sequence of bytes            */
			return (diva_strace_read_ie  (pVar, (diva_trace_ie_t*)variable));
		case 0x81: /* MI_INT    - signed integer                       */
			return (diva_strace_read_int (pVar, (int*)variable));
		case 0x82: /* MI_UINT   - unsigned integer                     */
			return (diva_strace_read_uint (pVar, (dword*)variable));
		case 0x83: /* MI_HINT   - unsigned integer, hex representetion */
			return (diva_strace_read_uint (pVar, (dword*)variable));
		case 0x87: /* MI_BITFLD - unsigned integer, bit representation */
			return (diva_strace_read_uint (pVar, (dword*)variable));
	}

	/*
		This type of variable is not handled, indicate error
		Or one problem in management interface, or in application recodeing
		table, or this application should handle it.
		*/
	return (-1);
}