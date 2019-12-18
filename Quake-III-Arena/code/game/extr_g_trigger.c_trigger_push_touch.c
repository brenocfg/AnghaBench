#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  trace_t ;
struct TYPE_6__ {int /*<<< orphan*/  s; TYPE_1__* client; } ;
typedef  TYPE_2__ gentity_t ;
struct TYPE_5__ {int /*<<< orphan*/  ps; } ;

/* Variables and functions */
 int /*<<< orphan*/  BG_TouchJumpPad (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

void trigger_push_touch (gentity_t *self, gentity_t *other, trace_t *trace ) {

	if ( !other->client ) {
		return;
	}

	BG_TouchJumpPad( &other->client->ps, &self->s );
}