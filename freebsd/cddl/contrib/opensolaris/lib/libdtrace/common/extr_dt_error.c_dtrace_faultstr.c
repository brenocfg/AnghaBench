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
typedef  int /*<<< orphan*/  dtrace_hdl_t ;

/* Variables and functions */
#define  DTRACEFLT_BADADDR 137 
#define  DTRACEFLT_BADALIGN 136 
#define  DTRACEFLT_BADSTACK 135 
#define  DTRACEFLT_DIVZERO 134 
#define  DTRACEFLT_ILLOP 133 
#define  DTRACEFLT_KPRIV 132 
#define  DTRACEFLT_LIBRARY 131 
#define  DTRACEFLT_NOSCRATCH 130 
#define  DTRACEFLT_TUPOFLOW 129 
#define  DTRACEFLT_UPRIV 128 

const char *
dtrace_faultstr(dtrace_hdl_t *dtp, int fault)
{
	int i;

	static const struct {
		int code;
		const char *str;
	} faults[] = {
		{ DTRACEFLT_BADADDR,	"invalid address" },
		{ DTRACEFLT_BADALIGN,	"invalid alignment" },
		{ DTRACEFLT_ILLOP,	"illegal operation" },
		{ DTRACEFLT_DIVZERO,	"divide-by-zero" },
		{ DTRACEFLT_NOSCRATCH,	"out of scratch space" },
		{ DTRACEFLT_KPRIV,	"invalid kernel access" },
		{ DTRACEFLT_UPRIV,	"invalid user access" },
		{ DTRACEFLT_TUPOFLOW,	"tuple stack overflow" },
		{ DTRACEFLT_BADSTACK,	"bad stack" },
		{ DTRACEFLT_LIBRARY,	"library-level fault" },
		{ 0,			NULL }
	};

	for (i = 0; faults[i].str != NULL; i++) {
		if (faults[i].code == fault)
			return (faults[i].str);
	}

	return ("unknown fault");
}