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
typedef  scalar_t__ uint32_t ;
struct pstore {int /*<<< orphan*/  next_free; scalar_t__ exceptions_per_area; } ;
typedef  int /*<<< orphan*/  chunk_t ;

/* Variables and functions */
 scalar_t__ NUM_SNAPSHOT_HDR_CHUNKS ; 
 scalar_t__ sector_div (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void skip_metadata(struct pstore *ps)
{
	uint32_t stride = ps->exceptions_per_area + 1;
	chunk_t next_free = ps->next_free;
	if (sector_div(next_free, stride) == NUM_SNAPSHOT_HDR_CHUNKS)
		ps->next_free++;
}