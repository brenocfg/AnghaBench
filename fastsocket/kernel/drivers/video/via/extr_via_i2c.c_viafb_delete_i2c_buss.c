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
struct viafb_par {TYPE_2__* shared; } ;
struct TYPE_3__ {int /*<<< orphan*/  adapter; } ;
struct TYPE_4__ {TYPE_1__ i2c_stuff; } ;

/* Variables and functions */
 int /*<<< orphan*/  i2c_del_adapter (int /*<<< orphan*/ *) ; 

void viafb_delete_i2c_buss(void *par)
{
	i2c_del_adapter(&((struct viafb_par *)par)->shared->i2c_stuff.adapter);
}