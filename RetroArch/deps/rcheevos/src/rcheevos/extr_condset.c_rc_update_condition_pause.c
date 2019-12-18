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
struct TYPE_3__ {int type; int pause; struct TYPE_3__* next; } ;
typedef  TYPE_1__ rc_condition_t ;

/* Variables and functions */
#define  RC_CONDITION_ADD_HITS 132 
#define  RC_CONDITION_ADD_SOURCE 131 
#define  RC_CONDITION_AND_NEXT 130 
#define  RC_CONDITION_PAUSE_IF 129 
#define  RC_CONDITION_SUB_SOURCE 128 

__attribute__((used)) static void rc_update_condition_pause(rc_condition_t* condition, int* in_pause) {
  if (condition->next != 0) {
    rc_update_condition_pause(condition->next, in_pause);
  }

  switch (condition->type) {
    case RC_CONDITION_PAUSE_IF:
      *in_pause = condition->pause = 1;
      break;
    
    case RC_CONDITION_ADD_SOURCE:
    case RC_CONDITION_SUB_SOURCE:
    case RC_CONDITION_ADD_HITS:
    case RC_CONDITION_AND_NEXT:
      condition->pause = *in_pause;
      break;
    
    default:
      *in_pause = condition->pause = 0;
      break;
  }
}