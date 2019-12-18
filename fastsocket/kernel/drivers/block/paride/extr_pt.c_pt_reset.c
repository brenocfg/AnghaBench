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
struct pt_unit {int /*<<< orphan*/  name; struct pi_adapter* pi; } ;
struct pi_adapter {int dummy; } ;

/* Variables and functions */
 int DRIVE (struct pt_unit*) ; 
 int HZ ; 
 int /*<<< orphan*/  PT_RESET_TMO ; 
 int STAT_BUSY ; 
 int /*<<< orphan*/  pi_connect (struct pi_adapter*) ; 
 int /*<<< orphan*/  pi_disconnect (struct pi_adapter*) ; 
 int /*<<< orphan*/  printk (char*,...) ; 
 int /*<<< orphan*/  pt_sleep (int) ; 
 int read_reg (struct pi_adapter*,int) ; 
 int status_reg (struct pi_adapter*) ; 
 scalar_t__ verbose ; 
 int /*<<< orphan*/  write_reg (struct pi_adapter*,int,int) ; 

__attribute__((used)) static int pt_reset(struct pt_unit *tape)
{
	struct pi_adapter *pi = tape->pi;
	int i, k, flg;
	int expect[5] = { 1, 1, 1, 0x14, 0xeb };

	pi_connect(pi);
	write_reg(pi, 6, DRIVE(tape));
	write_reg(pi, 7, 8);

	pt_sleep(20 * HZ / 1000);

	k = 0;
	while ((k++ < PT_RESET_TMO) && (status_reg(pi) & STAT_BUSY))
		pt_sleep(HZ / 10);

	flg = 1;
	for (i = 0; i < 5; i++)
		flg &= (read_reg(pi, i + 1) == expect[i]);

	if (verbose) {
		printk("%s: Reset (%d) signature = ", tape->name, k);
		for (i = 0; i < 5; i++)
			printk("%3x", read_reg(pi, i + 1));
		if (!flg)
			printk(" (incorrect)");
		printk("\n");
	}

	pi_disconnect(pi);
	return flg - 1;
}