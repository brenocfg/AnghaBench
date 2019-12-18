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
typedef  int mach_exception_data_type_t ;
typedef  int /*<<< orphan*/  kern_return_t ;

/* Variables and functions */
 int EXCEPTION_CODE_MAX ; 
 int /*<<< orphan*/  bsd_exception (int,int*,int) ; 

kern_return_t
do_bsdexception(
	    int exc,
	    int code,
	    int sub)
{
	mach_exception_data_type_t   codes[EXCEPTION_CODE_MAX];

	codes[0] = code;	
	codes[1] = sub;
	return(bsd_exception(exc, codes, 2));
}