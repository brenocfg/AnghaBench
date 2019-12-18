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
struct irq_desc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_S3C2443_WDT ; 
 int /*<<< orphan*/  s3c2443_irq_demux (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void s3c2443_irq_demux_wdtac97(unsigned int irq, struct irq_desc *desc)
{
	s3c2443_irq_demux(IRQ_S3C2443_WDT, 4);
}