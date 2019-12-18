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
struct TYPE_3__ {int valuecached; int /*<<< orphan*/  ptop; int /*<<< orphan*/  L; } ;
typedef  TYPE_1__ CapState ;

/* Variables and functions */
 int /*<<< orphan*/  lua_rawgeti (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  lua_replace (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  penvidx (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  subscache (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void updatecache_ (CapState *cs, int v) {
  lua_rawgeti(cs->L, penvidx(cs->ptop), v);
  lua_replace(cs->L, subscache(cs->ptop));
  cs->valuecached = v;
}