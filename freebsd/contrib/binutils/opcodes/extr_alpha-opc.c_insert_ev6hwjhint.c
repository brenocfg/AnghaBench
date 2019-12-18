#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */

/* Variables and functions */
 char* _ (char*) ; 

__attribute__((used)) static unsigned
insert_ev6hwjhint (unsigned insn, int value, const char **errmsg)
{
  if (errmsg != (const char **)NULL && (value & 3))
    *errmsg = _("jump hint unaligned");
  return insn | ((value / 4) & 0x1FFF);
}