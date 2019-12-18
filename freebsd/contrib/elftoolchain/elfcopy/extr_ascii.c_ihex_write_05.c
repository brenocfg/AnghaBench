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
typedef  int uint64_t ;

/* Variables and functions */
 int /*<<< orphan*/  ihex_write (int,int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  warnx (char*) ; 

__attribute__((used)) static void
ihex_write_05(int ofd, uint64_t e_entry)
{

	if (e_entry > 0xFFFFFFFF) {
		warnx("address space too big for Intel Hex file");
		return;
	}

	ihex_write(ofd, 5, 0, e_entry, NULL, 4);
}