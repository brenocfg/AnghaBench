#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct v3020 {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  gpio; } ;

/* Variables and functions */
 int ARRAY_SIZE (TYPE_1__*) ; 
 int /*<<< orphan*/  gpio_free (int /*<<< orphan*/ ) ; 
 TYPE_1__* v3020_gpio ; 

__attribute__((used)) static void v3020_gpio_unmap(struct v3020 *chip)
{
	int i;

	for (i = 0; i < ARRAY_SIZE(v3020_gpio); i++)
		gpio_free(v3020_gpio[i].gpio);
}