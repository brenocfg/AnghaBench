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
typedef  int /*<<< orphan*/  qboolean ;
struct TYPE_2__ {int line; } ;

/* Variables and functions */
 int /*<<< orphan*/  GetToken (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UnGetToken () ; 
 int /*<<< orphan*/  qfalse ; 
 int /*<<< orphan*/  qtrue ; 
 TYPE_1__* script ; 

qboolean TokenAvailable (void) {
	int		oldLine;
	qboolean	r;

	oldLine = script->line;
	r = GetToken( qtrue );
	if ( !r ) {
		return qfalse;
	}
	UnGetToken();
	if ( oldLine == script->line ) {
		return qtrue;
	}
	return qfalse;
}