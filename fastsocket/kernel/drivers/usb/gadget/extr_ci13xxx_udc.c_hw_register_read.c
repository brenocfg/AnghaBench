#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_2__ {size_t size; } ;

/* Variables and functions */
 int /*<<< orphan*/  hw_aread (unsigned int,int /*<<< orphan*/ ) ; 
 TYPE_1__ hw_bank ; 

__attribute__((used)) static size_t hw_register_read(u32 *buf, size_t size)
{
	unsigned i;

	if (size > hw_bank.size)
		size = hw_bank.size;

	for (i = 0; i < size; i++)
		buf[i] = hw_aread(i * sizeof(u32), ~0);

	return size;
}