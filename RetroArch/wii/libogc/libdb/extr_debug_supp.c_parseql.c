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
 char* fhstr2thread (char const*,int*) ; 
 int /*<<< orphan*/  hstr2byte (char const*,int*) ; 
 int /*<<< orphan*/  hstr2nibble (char const*,int*) ; 

s32 parseql(const char *in,s32 *first,s32 *max_cnt,s32 *athread)
{
	const char *ptr;

	ptr = in+2;
	if(!hstr2nibble(ptr,first)) return 0;

	ptr++;
	if(!hstr2byte(ptr,max_cnt)) return 0;

	ptr += 2;
	ptr = fhstr2thread(ptr,athread);
	if(ptr==NULL) return 0;

	return 1;
}