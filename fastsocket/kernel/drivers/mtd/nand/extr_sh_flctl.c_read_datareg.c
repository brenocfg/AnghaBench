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
struct sh_flctl {int /*<<< orphan*/ * done_buff; } ;

/* Variables and functions */
 int /*<<< orphan*/  FLDATAR (struct sh_flctl*) ; 
 unsigned long le32_to_cpu (unsigned long) ; 
 unsigned long readl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wait_completion (struct sh_flctl*) ; 

__attribute__((used)) static void read_datareg(struct sh_flctl *flctl, int offset)
{
	unsigned long data;
	unsigned long *buf = (unsigned long *)&flctl->done_buff[offset];

	wait_completion(flctl);

	data = readl(FLDATAR(flctl));
	*buf = le32_to_cpu(data);
}