#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int level; int /*<<< orphan*/  L; TYPE_1__* capture; } ;
struct TYPE_4__ {scalar_t__ len; } ;
typedef  TYPE_2__ MatchState ;

/* Variables and functions */
 scalar_t__ CAP_UNFINISHED ; 
 int luaL_error (int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static int check_capture (MatchState *ms, int l) {
  l -= '1';
  if (l < 0 || l >= ms->level || ms->capture[l].len == CAP_UNFINISHED)
    return luaL_error(ms->L, "invalid capture index %%%d", l + 1);
  return l;
}