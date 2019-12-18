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
struct TYPE_3__ {char const option; int (* function ) () ;} ;

/* Variables and functions */
 int ARRAY_SIZE (TYPE_1__*) ; 
 TYPE_1__* menu ; 
 int stub1 () ; 

__attribute__((used)) static int select_menu_item(const char arg)
{
	unsigned int i;

	for (i = ARRAY_SIZE(menu) - 1; i != 0; i--) {
		if (arg == menu[i].option)
			break;
	}

	return menu[i].function();
}