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
struct scoop_dev {scalar_t__ base; } ;

/* Variables and functions */
 scalar_t__ SCOOP_MCR ; 
 unsigned short ioread16 (scalar_t__) ; 
 int /*<<< orphan*/  iowrite16 (int,scalar_t__) ; 

__attribute__((used)) static void check_scoop_reg(struct scoop_dev *sdev)
{
	unsigned short mcr;

	mcr = ioread16(sdev->base + SCOOP_MCR);
	if ((mcr & 0x100) == 0)
		iowrite16(0x0101, sdev->base + SCOOP_MCR);
}