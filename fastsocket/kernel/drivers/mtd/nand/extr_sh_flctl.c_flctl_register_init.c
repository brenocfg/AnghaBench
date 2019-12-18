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
struct sh_flctl {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  FLCMNCR (struct sh_flctl*) ; 
 int /*<<< orphan*/  writel (unsigned long,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void flctl_register_init(struct sh_flctl *flctl, unsigned long val)
{
	writel(val, FLCMNCR(flctl));
}