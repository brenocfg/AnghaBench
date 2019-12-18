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
struct TYPE_2__ {unsigned long* read; } ;

/* Variables and functions */
 unsigned long IO_MASK (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  R_SERIAL0_READ ; 
 int /*<<< orphan*/  data_avail ; 
 int /*<<< orphan*/  data_in ; 
 TYPE_1__* kgdb_port ; 

int
getDebugChar(void)
{
	unsigned long readval;

	if (!kgdb_port)
		return 0;

	do {
		readval = *kgdb_port->read;
	} while (!(readval & IO_MASK(R_SERIAL0_READ, data_avail)));

	return (readval & IO_MASK(R_SERIAL0_READ, data_in));
}