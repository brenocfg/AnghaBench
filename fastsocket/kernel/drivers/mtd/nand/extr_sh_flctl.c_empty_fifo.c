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
 int /*<<< orphan*/  FLINTDMACR (struct sh_flctl*) ; 
 int /*<<< orphan*/  writel (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void empty_fifo(struct sh_flctl *flctl)
{
	writel(0x000c0000, FLINTDMACR(flctl));	/* FIFO Clear */
	writel(0x00000000, FLINTDMACR(flctl));	/* Clear Error flags */
}