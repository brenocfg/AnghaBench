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
struct simtec_i2c_data {int /*<<< orphan*/  reg; } ;

/* Variables and functions */
 int STATE_SCL ; 
 int readb (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int simtec_i2c_getscl(void *pw)
{
	struct simtec_i2c_data *pd = pw;
	return readb(pd->reg) & STATE_SCL ? 1 : 0;
}