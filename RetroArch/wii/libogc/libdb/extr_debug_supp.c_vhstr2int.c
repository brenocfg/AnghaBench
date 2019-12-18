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
 scalar_t__ hstr2nibble (char const*,int*) ; 

const char* vhstr2int(const char *buf,s32 *ival)
{
	s32 i,val,nibble;
	s32 found0,lim;

	found0 = 0;
	for(i=0;i<8;i++,buf++) {
		if(*buf!='0') break;

		found0 = 1;
	}

	val = 0;
	lim = 8 - i;
	for(i=0;i<lim;i++,buf++) {
		if(!hstr2nibble(buf,&nibble)) {
			if(i==0 && !found0) return NULL;

			*ival = val;
			return buf;
		}
		val = (val<<4)|nibble;
	}
	if(hstr2nibble(buf,&nibble)) return NULL;

	*ival = val;
	return buf;
}