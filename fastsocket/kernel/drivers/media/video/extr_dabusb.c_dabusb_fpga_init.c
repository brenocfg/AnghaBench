#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  pdabusb_t ;
typedef  TYPE_1__* pbulk_transfer_t ;
struct TYPE_4__ {int size; int* data; } ;

/* Variables and functions */
 int dabusb_bulk (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  dbg (char*) ; 

__attribute__((used)) static int dabusb_fpga_init (pdabusb_t s, pbulk_transfer_t b)
{
	b->size = 4;
	b->data[0] = 0x2c;
	b->data[1] = 0;
	b->data[2] = 0;
	b->data[3] = 0;

	dbg("dabusb_fpga_init");

	return dabusb_bulk (s, b);
}