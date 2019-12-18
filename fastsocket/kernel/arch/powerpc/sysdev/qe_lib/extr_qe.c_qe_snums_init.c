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
typedef  int u8 ;
struct TYPE_2__ {int num; int /*<<< orphan*/  state; } ;

/* Variables and functions */
 int /*<<< orphan*/  QE_SNUM_STATE_FREE ; 
 int qe_get_num_of_snums () ; 
 int qe_num_of_snum ; 
 TYPE_1__* snums ; 

__attribute__((used)) static void qe_snums_init(void)
{
	int i;
	static const u8 snum_init[] = {
		0x04, 0x05, 0x0C, 0x0D, 0x14, 0x15, 0x1C, 0x1D,
		0x24, 0x25, 0x2C, 0x2D, 0x34, 0x35, 0x88, 0x89,
		0x98, 0x99, 0xA8, 0xA9, 0xB8, 0xB9, 0xC8, 0xC9,
		0xD8, 0xD9, 0xE8, 0xE9, 0x08, 0x09, 0x18, 0x19,
		0x28, 0x29, 0x38, 0x39, 0x48, 0x49, 0x58, 0x59,
		0x68, 0x69, 0x78, 0x79, 0x80, 0x81,
	};

	qe_num_of_snum = qe_get_num_of_snums();

	for (i = 0; i < qe_num_of_snum; i++) {
		snums[i].num = snum_init[i];
		snums[i].state = QE_SNUM_STATE_FREE;
	}
}