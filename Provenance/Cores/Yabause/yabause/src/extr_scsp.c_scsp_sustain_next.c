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
struct TYPE_3__ {int /*<<< orphan*/  enxt; void* ecmp; int /*<<< orphan*/ * einc; void* ecnt; } ;
typedef  TYPE_1__ slot_t ;

/* Variables and functions */
 void* SCSP_ENV_DE ; 
 int /*<<< orphan*/  scsp_env_null_next ; 

__attribute__((used)) static void
scsp_sustain_next (slot_t *slot)
{
  // end of sustain happened, update to process the next phase...

  slot->ecnt = SCSP_ENV_DE;
  slot->einc = NULL;
  slot->ecmp = SCSP_ENV_DE + 1;
  slot->enxt = scsp_env_null_next;
}