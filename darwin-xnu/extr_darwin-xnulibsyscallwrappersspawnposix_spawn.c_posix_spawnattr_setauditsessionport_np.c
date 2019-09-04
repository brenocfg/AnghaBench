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
typedef  int /*<<< orphan*/  posix_spawnattr_t ;
typedef  int /*<<< orphan*/  mach_port_t ;
struct TYPE_3__ {int /*<<< orphan*/  new_port; int /*<<< orphan*/  port_type; } ;
typedef  TYPE_1__ _ps_port_action_t ;

/* Variables and functions */
 int /*<<< orphan*/  PSPA_AU_SESSION ; 
 int posix_spawn_appendportaction_np (int /*<<< orphan*/ *,TYPE_1__*) ; 

int    
posix_spawnattr_setauditsessionport_np(
		posix_spawnattr_t       *attr,
		mach_port_t              au_sessionport)
{
	_ps_port_action_t action = {
		.port_type = PSPA_AU_SESSION,
		.new_port = au_sessionport,
	};
	return posix_spawn_appendportaction_np(attr, &action);
}