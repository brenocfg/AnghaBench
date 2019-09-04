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
struct TYPE_2__ {int /*<<< orphan*/  offset64; } ;

/* Variables and functions */
 int /*<<< orphan*/  DBLMAP (int /*<<< orphan*/ ) ; 
 int IDTSZ ; 
 TYPE_1__* master_idt64 ; 

void idt64_remap(void) {
	for (int i = 0; i < IDTSZ; i++) {
		master_idt64[i].offset64 = DBLMAP(master_idt64[i].offset64);
	}
}