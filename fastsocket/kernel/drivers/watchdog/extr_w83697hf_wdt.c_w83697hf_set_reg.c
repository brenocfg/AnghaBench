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

/* Variables and functions */
 int /*<<< orphan*/  W83697HF_EFDR ; 
 int /*<<< orphan*/  W83697HF_EFIR ; 
 int /*<<< orphan*/  outb_p (unsigned char,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void w83697hf_set_reg(unsigned char reg, unsigned char data)
{
	outb_p(reg, W83697HF_EFIR);
	outb_p(data, W83697HF_EFDR);
}