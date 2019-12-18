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
struct TYPE_3__ {int /*<<< orphan*/  tts_event; scalar_t__ tts_user_tid; scalar_t__ tts_lwpid; scalar_t__ tts_pid; } ;
typedef  TYPE_1__ ttstate_t ;

/* Variables and functions */
 int /*<<< orphan*/  TTEVT_NONE ; 

__attribute__((used)) static void
clear_ttstate_t (ttstate_t *tts)
{
  tts->tts_pid = 0;
  tts->tts_lwpid = 0;
  tts->tts_user_tid = 0;
  tts->tts_event = TTEVT_NONE;
}