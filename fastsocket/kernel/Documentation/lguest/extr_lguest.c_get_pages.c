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
 int /*<<< orphan*/  errx (int,char*) ; 
 void* from_guest_phys (scalar_t__) ; 
 unsigned int getpagesize () ; 
 scalar_t__ guest_limit ; 
 scalar_t__ guest_max ; 

__attribute__((used)) static void *get_pages(unsigned int num)
{
	void *addr = from_guest_phys(guest_limit);

	guest_limit += num * getpagesize();
	if (guest_limit > guest_max)
		errx(1, "Not enough memory for devices");
	return addr;
}