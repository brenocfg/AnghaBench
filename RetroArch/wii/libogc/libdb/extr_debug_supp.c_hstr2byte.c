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
 int /*<<< orphan*/  hstr2nibble (char const*,int*) ; 

s32 hstr2byte(const char *buf,s32 *bval)
{
	s32 hnib,lnib;

	if(!hstr2nibble(buf,&hnib) || !hstr2nibble(buf+1,&lnib)) return 0;

	*bval = (hnib<<4)|lnib;
	return 1;
}