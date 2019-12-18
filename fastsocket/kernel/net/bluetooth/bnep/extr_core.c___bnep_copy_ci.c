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
struct TYPE_3__ {int /*<<< orphan*/  h_source; } ;
struct bnep_session {int /*<<< orphan*/  role; int /*<<< orphan*/  state; int /*<<< orphan*/  flags; TYPE_2__* dev; TYPE_1__ eh; } ;
struct bnep_conninfo {int /*<<< orphan*/  role; int /*<<< orphan*/  state; int /*<<< orphan*/  flags; int /*<<< orphan*/  device; int /*<<< orphan*/  dst; } ;
struct TYPE_4__ {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  ETH_ALEN ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void __bnep_copy_ci(struct bnep_conninfo *ci, struct bnep_session *s)
{
	memcpy(ci->dst, s->eh.h_source, ETH_ALEN);
	strcpy(ci->device, s->dev->name);
	ci->flags = s->flags;
	ci->state = s->state;
	ci->role  = s->role;
}