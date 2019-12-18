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
typedef  size_t u8 ;
struct xonar_cs43xx {size_t* cs4362a_regs; } ;
struct oxygen {struct xonar_cs43xx* model_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  cs4362a_write (struct oxygen*,size_t,size_t) ; 

__attribute__((used)) static void cs4362a_write_cached(struct oxygen *chip, u8 reg, u8 value)
{
	struct xonar_cs43xx *data = chip->model_data;

	if (value != data->cs4362a_regs[reg])
		cs4362a_write(chip, reg, value);
}