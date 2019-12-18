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
struct scrub_block {int /*<<< orphan*/  no_io_error_seen; } ;

/* Variables and functions */
 int /*<<< orphan*/  scrub_checksum (struct scrub_block*) ; 
 int /*<<< orphan*/  scrub_handle_errored_block (struct scrub_block*) ; 

__attribute__((used)) static void scrub_block_complete(struct scrub_block *sblock)
{
	if (!sblock->no_io_error_seen)
		scrub_handle_errored_block(sblock);
	else
		scrub_checksum(sblock);
}