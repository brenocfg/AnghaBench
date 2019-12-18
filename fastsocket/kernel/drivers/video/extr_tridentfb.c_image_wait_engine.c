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
struct tridentfb_par {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  cpu_relax () ; 
 int readmmr (struct tridentfb_par*,int) ; 

__attribute__((used)) static void image_wait_engine(struct tridentfb_par *par)
{
	while (readmmr(par, 0x2164) & 0xF0000000)
		cpu_relax();
}