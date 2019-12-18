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
struct pevent {int dummy; } ;

/* Variables and functions */
 unsigned long long data2host2 (struct pevent*,void const*) ; 
 unsigned long long data2host4 (struct pevent*,void const*) ; 
 unsigned long long data2host8 (struct pevent*,void const*) ; 

unsigned long long pevent_read_number(struct pevent *pevent,
				      const void *ptr, int size)
{
	switch (size) {
	case 1:
		return *(unsigned char *)ptr;
	case 2:
		return data2host2(pevent, ptr);
	case 4:
		return data2host4(pevent, ptr);
	case 8:
		return data2host8(pevent, ptr);
	default:
		/* BUG! */
		return 0;
	}
}