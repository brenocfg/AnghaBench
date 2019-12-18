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
struct seq_file {int dummy; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  seq_printf (struct seq_file*,char*,int,...) ; 
 int /*<<< orphan*/  to_i2c_client (struct device*) ; 
 int x1205_get_atrim (int /*<<< orphan*/ ,int*) ; 
 int x1205_get_dtrim (int /*<<< orphan*/ ,int*) ; 

__attribute__((used)) static int x1205_rtc_proc(struct device *dev, struct seq_file *seq)
{
	int err, dtrim, atrim;

	if ((err = x1205_get_dtrim(to_i2c_client(dev), &dtrim)) == 0)
		seq_printf(seq, "digital_trim\t: %d ppm\n", dtrim);

	if ((err = x1205_get_atrim(to_i2c_client(dev), &atrim)) == 0)
		seq_printf(seq, "analog_trim\t: %d.%02d pF\n",
			atrim / 1000, atrim % 1000);
	return 0;
}