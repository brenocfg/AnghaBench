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
typedef  int /*<<< orphan*/  u8 ;
struct nouveau_gpio {int dummy; } ;
struct dcb_gpio_func {int* log; int /*<<< orphan*/  line; } ;

/* Variables and functions */
 int nouveau_gpio_find (struct nouveau_gpio*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct dcb_gpio_func*) ; 
 int nouveau_gpio_sense (struct nouveau_gpio*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
nouveau_gpio_get(struct nouveau_gpio *gpio, int idx, u8 tag, u8 line)
{
	struct dcb_gpio_func func;
	int ret;

	ret = nouveau_gpio_find(gpio, idx, tag, line, &func);
	if (ret == 0) {
		ret = nouveau_gpio_sense(gpio, idx, func.line);
		if (ret >= 0)
			ret = (ret == (func.log[1] & 1));
	}

	return ret;
}