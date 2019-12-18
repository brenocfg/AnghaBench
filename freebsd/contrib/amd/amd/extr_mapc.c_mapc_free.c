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
typedef  scalar_t__ opaque_t ;
struct TYPE_4__ {scalar_t__ refc; int /*<<< orphan*/  hdr; struct TYPE_4__* map_name; } ;
typedef  TYPE_1__ mnt_map ;

/* Variables and functions */
 int /*<<< orphan*/  XFREE (TYPE_1__*) ; 
 int /*<<< orphan*/  mapc_clear (TYPE_1__*) ; 
 int /*<<< orphan*/  rem_que (int /*<<< orphan*/ *) ; 

void
mapc_free(opaque_t arg)
{
  mnt_map *m = (mnt_map *) arg;

  /*
   * Decrement the reference count.
   * If the reference count hits zero
   * then throw the map away.
   */
  if (m && --m->refc == 0) {
    mapc_clear(m);
    XFREE(m->map_name);
    rem_que(&m->hdr);
    XFREE(m);
  }
}