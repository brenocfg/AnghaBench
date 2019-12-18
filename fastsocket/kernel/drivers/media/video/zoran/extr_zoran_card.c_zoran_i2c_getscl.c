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
struct zoran {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ZR36057_I2CBR ; 
 int btread (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
zoran_i2c_getscl (void *data)
{
	struct zoran *zr = (struct zoran *) data;

	return btread(ZR36057_I2CBR) & 1;
}