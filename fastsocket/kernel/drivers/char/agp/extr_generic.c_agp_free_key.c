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
struct TYPE_2__ {int /*<<< orphan*/  key_list; } ;

/* Variables and functions */
 int MAXKEY ; 
 TYPE_1__* agp_bridge ; 
 int /*<<< orphan*/  clear_bit (int,int /*<<< orphan*/ ) ; 

void agp_free_key(int key)
{
	if (key < 0)
		return;

	if (key < MAXKEY)
		clear_bit(key, agp_bridge->key_list);
}