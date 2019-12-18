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
struct pcpu_chunk {scalar_t__ data; } ;

/* Variables and functions */
 int /*<<< orphan*/  pcpu_free_chunk (struct pcpu_chunk*) ; 
 int /*<<< orphan*/  pcpu_free_vm_areas (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pcpu_nr_groups ; 

__attribute__((used)) static void pcpu_destroy_chunk(struct pcpu_chunk *chunk)
{
	if (chunk && chunk->data)
		pcpu_free_vm_areas(chunk->data, pcpu_nr_groups);
	pcpu_free_chunk(chunk);
}