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
struct pg {int /*<<< orphan*/  pi; int /*<<< orphan*/  name; } ;
typedef  int /*<<< orphan*/  got ;

/* Variables and functions */
 int DRIVE (struct pg*) ; 
 int HZ ; 
 int /*<<< orphan*/  PG_RESET_TMO ; 
 int STAT_BUSY ; 
 scalar_t__ memcmp (int*,int*,int) ; 
 int /*<<< orphan*/  pg_sleep (int) ; 
 int /*<<< orphan*/  pi_connect (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pi_disconnect (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printk (char*,...) ; 
 int read_reg (struct pg*,int) ; 
 int status_reg (struct pg*) ; 
 scalar_t__ verbose ; 
 int /*<<< orphan*/  write_reg (struct pg*,int,int) ; 

__attribute__((used)) static int pg_reset(struct pg *dev)
{
	int i, k, err;
	int expect[5] = { 1, 1, 1, 0x14, 0xeb };
	int got[5];

	pi_connect(dev->pi);
	write_reg(dev, 6, DRIVE(dev));
	write_reg(dev, 7, 8);

	pg_sleep(20 * HZ / 1000);

	k = 0;
	while ((k++ < PG_RESET_TMO) && (status_reg(dev) & STAT_BUSY))
		pg_sleep(1);

	for (i = 0; i < 5; i++)
		got[i] = read_reg(dev, i + 1);

	err = memcmp(expect, got, sizeof(got)) ? -1 : 0;

	if (verbose) {
		printk("%s: Reset (%d) signature = ", dev->name, k);
		for (i = 0; i < 5; i++)
			printk("%3x", got[i]);
		if (err)
			printk(" (incorrect)");
		printk("\n");
	}

	pi_disconnect(dev->pi);
	return err;
}