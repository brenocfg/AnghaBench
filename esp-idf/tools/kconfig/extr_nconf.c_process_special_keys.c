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
struct menu {int dummy; } ;
struct TYPE_2__ {int key; int /*<<< orphan*/  (* handler ) (int*,struct menu*) ;} ;

/* Variables and functions */
 int KEY_F (int) ; 
 int KEY_RESIZE ; 
 TYPE_1__* function_keys ; 
 int function_keys_num ; 
 int /*<<< orphan*/  setup_windows () ; 
 int /*<<< orphan*/  stub1 (int*,struct menu*) ; 

__attribute__((used)) static int process_special_keys(int *key, struct menu *menu)
{
	int i;

	if (*key == KEY_RESIZE) {
		setup_windows();
		return 1;
	}

	for (i = 0; i < function_keys_num; i++) {
		if (*key == KEY_F(function_keys[i].key) ||
		    *key == '0' + function_keys[i].key){
			function_keys[i].handler(key, menu);
			return 1;
		}
	}

	return 0;
}