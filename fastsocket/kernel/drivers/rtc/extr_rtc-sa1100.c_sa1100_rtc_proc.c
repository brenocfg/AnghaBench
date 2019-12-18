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
typedef  char* u32 ;
struct seq_file {int dummy; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int OIER ; 
 int OIER_E1 ; 
 int RTSR ; 
 int RTSR_HZE ; 
 scalar_t__ RTTR ; 
 char* rtc_freq ; 
 int /*<<< orphan*/  seq_printf (struct seq_file*,char*,char*) ; 

__attribute__((used)) static int sa1100_rtc_proc(struct device *dev, struct seq_file *seq)
{
	seq_printf(seq, "trim/divider\t: 0x%08x\n", (u32) RTTR);
	seq_printf(seq, "update_IRQ\t: %s\n",
			(RTSR & RTSR_HZE) ? "yes" : "no");
	seq_printf(seq, "periodic_IRQ\t: %s\n",
			(OIER & OIER_E1) ? "yes" : "no");
	seq_printf(seq, "periodic_freq\t: %ld\n", rtc_freq);

	return 0;
}