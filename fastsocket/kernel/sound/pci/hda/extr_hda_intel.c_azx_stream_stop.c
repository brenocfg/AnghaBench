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
struct azx_dev {int index; } ;
struct azx {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  INTCTL ; 
 int azx_readl (struct azx*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  azx_stream_clear (struct azx*,struct azx_dev*) ; 
 int /*<<< orphan*/  azx_writel (struct azx*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void azx_stream_stop(struct azx *chip, struct azx_dev *azx_dev)
{
	azx_stream_clear(chip, azx_dev);
	/* disable SIE */
	azx_writel(chip, INTCTL,
		   azx_readl(chip, INTCTL) & ~(1 << azx_dev->index));
}