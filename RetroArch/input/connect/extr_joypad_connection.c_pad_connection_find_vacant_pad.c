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
struct TYPE_4__ {int /*<<< orphan*/  connected; } ;
typedef  TYPE_1__ joypad_connection_t ;

/* Variables and functions */
 int /*<<< orphan*/  joypad_is_end_of_list (TYPE_1__*) ; 

int pad_connection_find_vacant_pad(joypad_connection_t *joyconn)
{
  unsigned i;

  if (!joyconn)
    return -1;

  for (i = 0; !joypad_is_end_of_list(&joyconn[i]); i++)
  {
    if(!joyconn[i].connected)
      return i;
  }

  return -1;
}