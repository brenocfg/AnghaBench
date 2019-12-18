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
struct dm_buffer {int /*<<< orphan*/  block; } ;
typedef  int /*<<< orphan*/  sector_t ;

/* Variables and functions */

sector_t dm_bufio_get_block_number(struct dm_buffer *b)
{
	return b->block;
}