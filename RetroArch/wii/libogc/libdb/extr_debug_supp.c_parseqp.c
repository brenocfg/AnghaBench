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
typedef  int s32 ;

/* Variables and functions */
 char* fhstr2int (char const*,int*) ; 
 char* fhstr2thread (char const*,int*) ; 

s32 parseqp(const char *in,s32 *mask,s32 *thread)
{
	const char *ptr;

	ptr = fhstr2int(in+2,mask);
	if(ptr==NULL) return 0;

	ptr = fhstr2thread(ptr,thread);
	if(ptr==NULL) return 0;

	return 1;
}