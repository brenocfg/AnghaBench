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
typedef  enum ipl_type { ____Placeholder_ipl_type } ipl_type ;

/* Variables and functions */
 char* IPL_CCW_STR ; 
 char* IPL_FCP_DUMP_STR ; 
 char* IPL_FCP_STR ; 
 char* IPL_NSS_STR ; 
#define  IPL_TYPE_CCW 132 
#define  IPL_TYPE_FCP 131 
#define  IPL_TYPE_FCP_DUMP 130 
#define  IPL_TYPE_NSS 129 
#define  IPL_TYPE_UNKNOWN 128 
 char* IPL_UNKNOWN_STR ; 

__attribute__((used)) static char *ipl_type_str(enum ipl_type type)
{
	switch (type) {
	case IPL_TYPE_CCW:
		return IPL_CCW_STR;
	case IPL_TYPE_FCP:
		return IPL_FCP_STR;
	case IPL_TYPE_FCP_DUMP:
		return IPL_FCP_DUMP_STR;
	case IPL_TYPE_NSS:
		return IPL_NSS_STR;
	case IPL_TYPE_UNKNOWN:
	default:
		return IPL_UNKNOWN_STR;
	}
}