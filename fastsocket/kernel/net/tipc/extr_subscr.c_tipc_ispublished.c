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
typedef  int /*<<< orphan*/  u32 ;
struct tipc_name {int /*<<< orphan*/  instance; int /*<<< orphan*/  type; } ;

/* Variables and functions */
 scalar_t__ tipc_nametbl_translate (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

int tipc_ispublished(struct tipc_name const *name)
{
	u32 domain = 0;

	return(tipc_nametbl_translate(name->type, name->instance,&domain) != 0);
}