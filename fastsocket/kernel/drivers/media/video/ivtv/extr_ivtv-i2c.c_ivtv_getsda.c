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
struct ivtv {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  IVTV_REG_I2C_GETSDA_OFFSET ; 
 int read_reg (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ivtv_getsda(struct ivtv *itv)
{
	return read_reg(IVTV_REG_I2C_GETSDA_OFFSET) & 1;
}