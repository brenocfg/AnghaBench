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
typedef  int /*<<< orphan*/  u64 ;
typedef  int /*<<< orphan*/  u32 ;
struct io_ctl {int num_pages; int size; int /*<<< orphan*/ * cur; scalar_t__ check_crcs; } ;
typedef  int /*<<< orphan*/  __le64 ;

/* Variables and functions */
 int /*<<< orphan*/  cpu_to_le64 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  io_ctl_map_page (struct io_ctl*,int) ; 

__attribute__((used)) static void io_ctl_set_generation(struct io_ctl *io_ctl, u64 generation)
{
	__le64 *val;

	io_ctl_map_page(io_ctl, 1);

	/*
	 * Skip the csum areas.  If we don't check crcs then we just have a
	 * 64bit chunk at the front of the first page.
	 */
	if (io_ctl->check_crcs) {
		io_ctl->cur += (sizeof(u32) * io_ctl->num_pages);
		io_ctl->size -= sizeof(u64) + (sizeof(u32) * io_ctl->num_pages);
	} else {
		io_ctl->cur += sizeof(u64);
		io_ctl->size -= sizeof(u64) * 2;
	}

	val = io_ctl->cur;
	*val = cpu_to_le64(generation);
	io_ctl->cur += sizeof(u64);
}