#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  menu_id ;
struct TYPE_4__ {int enabled; } ;
typedef  TYPE_1__ menu_entry ;

/* Variables and functions */
 int me_id2offset (TYPE_1__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void me_enable(menu_entry *entries, menu_id id, int enable)
{
	int i = me_id2offset(entries, id);
	entries[i].enabled = enable;
}