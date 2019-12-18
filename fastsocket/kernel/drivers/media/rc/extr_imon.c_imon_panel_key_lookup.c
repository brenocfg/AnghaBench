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
typedef  int u64 ;
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_3__ {int hw_code; int /*<<< orphan*/  keycode; } ;

/* Variables and functions */
 int ARRAY_SIZE (TYPE_1__*) ; 
 int /*<<< orphan*/  KEY_RESERVED ; 
 TYPE_1__* imon_panel_key_table ; 

__attribute__((used)) static u32 imon_panel_key_lookup(u64 code)
{
	int i;
	u32 keycode = KEY_RESERVED;

	for (i = 0; i < ARRAY_SIZE(imon_panel_key_table); i++) {
		if (imon_panel_key_table[i].hw_code == (code | 0xffee)) {
			keycode = imon_panel_key_table[i].keycode;
			break;
		}
	}

	return keycode;
}