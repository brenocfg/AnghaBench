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

/* Variables and functions */
 int FIT_MAJOR (unsigned long) ; 
 int FIT_MINOR (unsigned long) ; 
 unsigned int FIT_TYPE (unsigned long) ; 
 char* fit_type_name (unsigned int) ; 
 int sprintf (char*,char*,unsigned int,char*,int,int,unsigned long,unsigned int) ; 

__attribute__((used)) static int dump_fit_entry(char *page, unsigned long *fentry)
{
	unsigned type;

	type = FIT_TYPE(fentry[1]);
	return sprintf(page, "%02x %-25s %x.%02x %016lx %u\n",
		       type,
		       fit_type_name(type),
		       FIT_MAJOR(fentry[1]), FIT_MINOR(fentry[1]),
		       fentry[0],
		       /* mult by sixteen to get size in bytes */
		       (unsigned)(fentry[1] & 0xffffff) * 16);
}