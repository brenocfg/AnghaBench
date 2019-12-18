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
 unsigned long long __data2host8 (struct pevent*,unsigned long long) ; 
 int /*<<< orphan*/  read_or_die (unsigned long long*,int) ; 

__attribute__((used)) static unsigned long long read8(struct pevent *pevent)
{
	unsigned long long data;

	read_or_die(&data, 8);
	return __data2host8(pevent, data);
}