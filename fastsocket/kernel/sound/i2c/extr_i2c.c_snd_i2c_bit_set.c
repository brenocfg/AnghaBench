#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {TYPE_1__* bit; } ;
struct snd_i2c_bus {TYPE_2__ hw_ops; } ;
struct TYPE_3__ {int /*<<< orphan*/  (* setlines ) (struct snd_i2c_bus*,int,int) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (struct snd_i2c_bus*,int,int) ; 

__attribute__((used)) static void snd_i2c_bit_set(struct snd_i2c_bus *bus, int clock, int data)
{
	bus->hw_ops.bit->setlines(bus, clock, data);
}