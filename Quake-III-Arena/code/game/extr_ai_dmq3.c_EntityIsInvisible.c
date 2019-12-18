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
typedef  int /*<<< orphan*/  qboolean ;
struct TYPE_4__ {int powerups; } ;
typedef  TYPE_1__ aas_entityinfo_t ;

/* Variables and functions */
 scalar_t__ EntityCarriesFlag (TYPE_1__*) ; 
 int PW_INVIS ; 
 int /*<<< orphan*/  qfalse ; 
 int /*<<< orphan*/  qtrue ; 

qboolean EntityIsInvisible(aas_entityinfo_t *entinfo) {
	// the flag is always visible
	if (EntityCarriesFlag(entinfo)) {
		return qfalse;
	}
	if (entinfo->powerups & (1 << PW_INVIS)) {
		return qtrue;
	}
	return qfalse;
}