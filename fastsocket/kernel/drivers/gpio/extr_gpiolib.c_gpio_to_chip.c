#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct gpio_chip {int dummy; } ;
struct TYPE_2__ {struct gpio_chip* chip; } ;

/* Variables and functions */
 TYPE_1__* gpio_desc ; 

__attribute__((used)) static inline struct gpio_chip *gpio_to_chip(unsigned gpio)
{
	return gpio_desc[gpio].chip;
}