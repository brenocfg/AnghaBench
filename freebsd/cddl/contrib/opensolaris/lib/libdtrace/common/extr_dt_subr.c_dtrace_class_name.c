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
typedef  int dtrace_class_t ;

/* Variables and functions */
#define  DTRACE_CLASS_COMMON 133 
#define  DTRACE_CLASS_CPU 132 
#define  DTRACE_CLASS_GROUP 131 
#define  DTRACE_CLASS_ISA 130 
#define  DTRACE_CLASS_PLATFORM 129 
#define  DTRACE_CLASS_UNKNOWN 128 

const char *
dtrace_class_name(dtrace_class_t c)
{
	switch (c) {
	case DTRACE_CLASS_UNKNOWN:	return ("Unknown");
	case DTRACE_CLASS_CPU:		return ("CPU");
	case DTRACE_CLASS_PLATFORM:	return ("Platform");
	case DTRACE_CLASS_GROUP:	return ("Group");
	case DTRACE_CLASS_ISA:		return ("ISA");
	case DTRACE_CLASS_COMMON:	return ("Common");
	default:			return (NULL);
	}
}