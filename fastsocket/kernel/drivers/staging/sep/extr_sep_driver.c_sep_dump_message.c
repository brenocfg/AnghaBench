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
typedef  int /*<<< orphan*/  u32 ;
struct sep_device {scalar_t__ shared_addr; } ;

/* Variables and functions */
 int /*<<< orphan*/  edbg (char*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void sep_dump_message(struct sep_device *sep)
{
	int count;
	for (count = 0; count < 12 * 4; count += 4)
		edbg("Word %d of the message is %u\n", count, *((u32 *) (sep->shared_addr + count)));
}