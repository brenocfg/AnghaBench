#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {TYPE_3__* next; TYPE_3__* prev; } ;
struct TYPE_5__ {TYPE_2__ l; } ;
struct TYPE_7__ {TYPE_1__ u; } ;
typedef  TYPE_3__ UpVal ;

/* Variables and functions */
 int /*<<< orphan*/  lua_assert (int) ; 

__attribute__((used)) static void unlinkupval (UpVal *uv) {
  lua_assert(uv->u.l.next->u.l.prev == uv && uv->u.l.prev->u.l.next == uv);
  uv->u.l.next->u.l.prev = uv->u.l.prev;  /* remove from `uvhead' list */
  uv->u.l.prev->u.l.next = uv->u.l.next;
}