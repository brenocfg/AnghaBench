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
struct TYPE_2__ {int is_paused; int /*<<< orphan*/  player; } ;
typedef  TYPE_1__ sl_t ;

/* Variables and functions */
 scalar_t__ SLPlayItf_SetPlayState (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SL_PLAYSTATE_PLAYING ; 
 scalar_t__ SL_RESULT_SUCCESS ; 

__attribute__((used)) static bool sl_start(void *data, bool is_shutdown)
{
   sl_t      *sl = (sl_t*)data;
   sl->is_paused = (SLPlayItf_SetPlayState(sl->player, SL_PLAYSTATE_PLAYING)
         == SL_RESULT_SUCCESS) ? false : true;
   return sl->is_paused ? false : true;
}