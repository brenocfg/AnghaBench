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
struct nouveau_gpio {int (* drive ) (struct nouveau_gpio*,int,int,int) ;} ;

/* Variables and functions */
 int ENODEV ; 
 int stub1 (struct nouveau_gpio*,int,int,int) ; 

__attribute__((used)) static int
nouveau_gpio_drive(struct nouveau_gpio *gpio,
		   int idx, int line, int dir, int out)
{
	return gpio->drive ? gpio->drive(gpio, line, dir, out) : -ENODEV;
}