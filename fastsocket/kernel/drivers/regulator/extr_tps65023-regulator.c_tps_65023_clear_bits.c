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
struct tps_pmic {int /*<<< orphan*/  io_lock; TYPE_1__* client; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int tps_65023_read (struct tps_pmic*,int) ; 
 int tps_65023_write (struct tps_pmic*,int,int) ; 

__attribute__((used)) static int tps_65023_clear_bits(struct tps_pmic *tps, u8 reg, u8 mask)
{
	int err, data;

	mutex_lock(&tps->io_lock);

	data = tps_65023_read(tps, reg);
	if (data < 0) {
		dev_err(&tps->client->dev, "Read from reg 0x%x failed\n", reg);
		err = data;
		goto out;
	}

	data &= ~mask;

	err = tps_65023_write(tps, reg, data);
	if (err)
		dev_err(&tps->client->dev, "Write for reg 0x%x failed\n", reg);

out:
	mutex_unlock(&tps->io_lock);
	return err;

}