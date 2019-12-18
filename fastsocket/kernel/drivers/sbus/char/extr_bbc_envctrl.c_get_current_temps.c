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
struct bbc_cpu_temperature {scalar_t__ curr_amb_temp; scalar_t__ curr_cpu_temp; int /*<<< orphan*/  index; int /*<<< orphan*/  client; scalar_t__ prev_cpu_temp; scalar_t__ prev_amb_temp; } ;

/* Variables and functions */
 int /*<<< orphan*/  MAX1617_AMB_TEMP ; 
 int /*<<< orphan*/  MAX1617_CPU_TEMP ; 
 int /*<<< orphan*/  bbc_i2c_readb (int /*<<< orphan*/ ,unsigned char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printk (char*,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static void get_current_temps(struct bbc_cpu_temperature *tp)
{
	tp->prev_amb_temp = tp->curr_amb_temp;
	bbc_i2c_readb(tp->client,
		      (unsigned char *) &tp->curr_amb_temp,
		      MAX1617_AMB_TEMP);
	tp->prev_cpu_temp = tp->curr_cpu_temp;
	bbc_i2c_readb(tp->client,
		      (unsigned char *) &tp->curr_cpu_temp,
		      MAX1617_CPU_TEMP);
#ifdef ENVCTRL_TRACE
	printk("temp%d: cpu(%d C) amb(%d C)\n",
	       tp->index,
	       (int) tp->curr_cpu_temp, (int) tp->curr_amb_temp);
#endif
}