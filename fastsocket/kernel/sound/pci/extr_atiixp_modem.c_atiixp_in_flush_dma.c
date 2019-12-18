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
struct atiixp_modem {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ATI_REG_MODEM_FIFO_IN_FLUSH ; 
 int /*<<< orphan*/  MODEM_FIFO_FLUSH ; 
 int /*<<< orphan*/  atiixp_write (struct atiixp_modem*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void atiixp_in_flush_dma(struct atiixp_modem *chip)
{
	atiixp_write(chip, MODEM_FIFO_FLUSH, ATI_REG_MODEM_FIFO_IN_FLUSH);
}