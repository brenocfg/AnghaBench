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
typedef  int uint_t ;

/* Variables and functions */
#define  DT_IDENT_ACTFUNC 141 
#define  DT_IDENT_AGG 140 
#define  DT_IDENT_AGGFUNC 139 
#define  DT_IDENT_ARRAY 138 
#define  DT_IDENT_ENUM 137 
#define  DT_IDENT_FUNC 136 
#define  DT_IDENT_PRAGAT 135 
#define  DT_IDENT_PRAGBN 134 
#define  DT_IDENT_PROBE 133 
#define  DT_IDENT_PTR 132 
#define  DT_IDENT_SCALAR 131 
#define  DT_IDENT_SYMBOL 130 
#define  DT_IDENT_XLPTR 129 
#define  DT_IDENT_XLSOU 128 

const char *
dt_idkind_name(uint_t kind)
{
	switch (kind) {
	case DT_IDENT_ARRAY:	return ("associative array");
	case DT_IDENT_SCALAR:	return ("scalar");
	case DT_IDENT_PTR:	return ("pointer");
	case DT_IDENT_FUNC:	return ("function");
	case DT_IDENT_AGG:	return ("aggregation");
	case DT_IDENT_AGGFUNC:	return ("aggregating function");
	case DT_IDENT_ACTFUNC:	return ("tracing function");
	case DT_IDENT_XLSOU:	return ("translated data");
	case DT_IDENT_XLPTR:	return ("pointer to translated data");
	case DT_IDENT_SYMBOL:	return ("external symbol reference");
	case DT_IDENT_ENUM:	return ("enumerator");
	case DT_IDENT_PRAGAT:	return ("#pragma attributes");
	case DT_IDENT_PRAGBN:	return ("#pragma binding");
	case DT_IDENT_PROBE:	return ("probe definition");
	default:		return ("<?>");
	}
}