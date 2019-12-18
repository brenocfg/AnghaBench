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
typedef  scalar_t__ u8 ;
struct oxygen {struct dg* model_data; } ;
struct dg {scalar_t__* cs4245_regs; } ;

/* Variables and functions */
 int /*<<< orphan*/  cs4245_write (struct oxygen*,unsigned int,scalar_t__) ; 

__attribute__((used)) static void cs4245_write_cached(struct oxygen *chip, unsigned int reg, u8 value)
{
	struct dg *data = chip->model_data;

	if (value != data->cs4245_regs[reg])
		cs4245_write(chip, reg, value);
}