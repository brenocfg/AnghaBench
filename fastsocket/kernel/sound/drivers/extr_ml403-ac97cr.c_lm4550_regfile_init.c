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
struct TYPE_2__ {int flag; int /*<<< orphan*/  def; int /*<<< orphan*/  value; } ;

/* Variables and functions */
 int LM4550_REG_FAKEPROBE ; 
 TYPE_1__* lm4550_regfile ; 

__attribute__((used)) static void lm4550_regfile_init(void)
{
	int i;
	for (i = 0; i < 64; i++)
		if (lm4550_regfile[i].flag & LM4550_REG_FAKEPROBE)
			lm4550_regfile[i].value = lm4550_regfile[i].def;
}