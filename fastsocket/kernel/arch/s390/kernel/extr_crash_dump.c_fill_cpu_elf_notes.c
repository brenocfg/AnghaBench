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
struct save_area_s390x {int dummy; } ;

/* Variables and functions */
 void* nt_fpregset (void*,struct save_area_s390x*) ; 
 void* nt_prstatus (void*,struct save_area_s390x*) ; 
 void* nt_s390_ctrs (void*,struct save_area_s390x*) ; 
 void* nt_s390_prefix (void*,struct save_area_s390x*) ; 
 void* nt_s390_timer (void*,struct save_area_s390x*) ; 
 void* nt_s390_tod_cmp (void*,struct save_area_s390x*) ; 
 void* nt_s390_tod_preg (void*,struct save_area_s390x*) ; 

void *fill_cpu_elf_notes(void *ptr, struct save_area_s390x *sa)
{
	ptr = nt_prstatus(ptr, sa);
	ptr = nt_fpregset(ptr, sa);
	ptr = nt_s390_timer(ptr, sa);
	ptr = nt_s390_tod_cmp(ptr, sa);
	ptr = nt_s390_tod_preg(ptr, sa);
	ptr = nt_s390_ctrs(ptr, sa);
	ptr = nt_s390_prefix(ptr, sa);
	return ptr;
}