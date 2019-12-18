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
struct n2rng {TYPE_1__* op; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EAGAIN ; 
 int ENODEV ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int n2rng_try_read_ctl (struct n2rng*) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static int n2rng_grab_diag_control(struct n2rng *np)
{
	int i, busy_count, err = -ENODEV;

	busy_count = 0;
	for (i = 0; i < 100; i++) {
		err = n2rng_try_read_ctl(np);
		if (err != -EAGAIN)
			break;

		if (++busy_count > 100) {
			dev_err(&np->op->dev,
				"Grab diag control timeout.\n");
			return -ENODEV;
		}

		udelay(1);
	}

	return err;
}