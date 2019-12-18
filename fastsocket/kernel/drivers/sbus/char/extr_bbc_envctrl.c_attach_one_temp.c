#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct of_device {int dummy; } ;
struct bbc_i2c_bus {int /*<<< orphan*/  temps; } ;
struct bbc_cpu_temperature {int index; void** fan_todo; int /*<<< orphan*/  curr_amb_temp; int /*<<< orphan*/  avg_amb_temp; int /*<<< orphan*/  prev_amb_temp; int /*<<< orphan*/  curr_cpu_temp; int /*<<< orphan*/  avg_cpu_temp; int /*<<< orphan*/  prev_cpu_temp; int /*<<< orphan*/  client; int /*<<< orphan*/  bp_list; int /*<<< orphan*/  glob_list; } ;
struct TYPE_4__ {int high_pwroff; int low_pwroff; } ;
struct TYPE_3__ {int high_pwroff; int low_pwroff; } ;

/* Variables and functions */
 size_t FAN_AMBIENT ; 
 size_t FAN_CPU ; 
 void* FAN_SAME ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  MAX1617_WR_AMB_HIGHLIM ; 
 int /*<<< orphan*/  MAX1617_WR_AMB_LOWLIM ; 
 int /*<<< orphan*/  MAX1617_WR_CFG_BYTE ; 
 int /*<<< orphan*/  MAX1617_WR_CPU_HIGHLIM ; 
 int /*<<< orphan*/  MAX1617_WR_CPU_LOWLIM ; 
 int /*<<< orphan*/  MAX1617_WR_CVRATE_BYTE ; 
 int /*<<< orphan*/  all_temps ; 
 TYPE_2__* amb_temp_limits ; 
 int /*<<< orphan*/  bbc_i2c_attach (struct bbc_i2c_bus*,struct of_device*) ; 
 int /*<<< orphan*/  bbc_i2c_writeb (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 TYPE_1__* cpu_temp_limits ; 
 int /*<<< orphan*/  get_current_temps (struct bbc_cpu_temperature*) ; 
 int /*<<< orphan*/  kfree (struct bbc_cpu_temperature*) ; 
 struct bbc_cpu_temperature* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void attach_one_temp(struct bbc_i2c_bus *bp, struct of_device *op,
			    int temp_idx)
{
	struct bbc_cpu_temperature *tp;

	tp = kzalloc(sizeof(*tp), GFP_KERNEL);
	if (!tp)
		return;

	tp->client = bbc_i2c_attach(bp, op);
	if (!tp->client) {
		kfree(tp);
		return;
	}


	tp->index = temp_idx;

	list_add(&tp->glob_list, &all_temps);
	list_add(&tp->bp_list, &bp->temps);

	/* Tell it to convert once every 5 seconds, clear all cfg
	 * bits.
	 */
	bbc_i2c_writeb(tp->client, 0x00, MAX1617_WR_CFG_BYTE);
	bbc_i2c_writeb(tp->client, 0x02, MAX1617_WR_CVRATE_BYTE);

	/* Program the hard temperature limits into the chip. */
	bbc_i2c_writeb(tp->client, amb_temp_limits[tp->index].high_pwroff,
		       MAX1617_WR_AMB_HIGHLIM);
	bbc_i2c_writeb(tp->client, amb_temp_limits[tp->index].low_pwroff,
		       MAX1617_WR_AMB_LOWLIM);
	bbc_i2c_writeb(tp->client, cpu_temp_limits[tp->index].high_pwroff,
		       MAX1617_WR_CPU_HIGHLIM);
	bbc_i2c_writeb(tp->client, cpu_temp_limits[tp->index].low_pwroff,
		       MAX1617_WR_CPU_LOWLIM);

	get_current_temps(tp);
	tp->prev_cpu_temp = tp->avg_cpu_temp = tp->curr_cpu_temp;
	tp->prev_amb_temp = tp->avg_amb_temp = tp->curr_amb_temp;

	tp->fan_todo[FAN_AMBIENT] = FAN_SAME;
	tp->fan_todo[FAN_CPU] = FAN_SAME;
}