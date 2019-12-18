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
struct agp_memory {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  agp_free_memory (struct agp_memory*) ; 
 int /*<<< orphan*/  agp_remove_from_pool (struct agp_memory*) ; 

void agp_free_memory_wrap(struct agp_memory *memory)
{
	agp_remove_from_pool(memory);
	agp_free_memory(memory);
}