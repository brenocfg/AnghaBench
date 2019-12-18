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
struct TYPE_2__ {scalar_t__ index; int /*<<< orphan*/  size; int /*<<< orphan*/  offset; } ;

/* Variables and functions */
 TYPE_1__* cpu_data ; 
 scalar_t__ page_size ; 

__attribute__((used)) static void update_cpu_data_index(int cpu)
{
	cpu_data[cpu].offset += page_size;
	cpu_data[cpu].size -= page_size;
	cpu_data[cpu].index = 0;
}