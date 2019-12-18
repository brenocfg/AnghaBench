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
struct snd_i2c_bus {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  snd_i2c_bit_hw_stop (struct snd_i2c_bus*) ; 
 int /*<<< orphan*/  snd_i2c_bit_set (struct snd_i2c_bus*,int,int) ; 

__attribute__((used)) static void snd_i2c_bit_stop(struct snd_i2c_bus *bus)
{
	snd_i2c_bit_set(bus, 0, 0);
	snd_i2c_bit_set(bus, 1, 0);
	snd_i2c_bit_set(bus, 1, 1);
	snd_i2c_bit_hw_stop(bus);
}