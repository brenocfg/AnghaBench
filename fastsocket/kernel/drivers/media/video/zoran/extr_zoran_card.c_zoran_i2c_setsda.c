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
struct zoran {int i2cbr; } ;

/* Variables and functions */
 int /*<<< orphan*/  ZR36057_I2CBR ; 
 int /*<<< orphan*/  btwrite (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
zoran_i2c_setsda (void *data,
		  int   state)
{
	struct zoran *zr = (struct zoran *) data;

	if (state)
		zr->i2cbr |= 2;
	else
		zr->i2cbr &= ~2;
	btwrite(zr->i2cbr, ZR36057_I2CBR);
}