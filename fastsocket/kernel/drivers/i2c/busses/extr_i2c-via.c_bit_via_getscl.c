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

/* Variables and functions */
 int /*<<< orphan*/  I2C_IN ; 
 int I2C_SCL ; 
 int inb (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int bit_via_getscl(void *data)
{
	return (0 != (inb(I2C_IN) & I2C_SCL));
}