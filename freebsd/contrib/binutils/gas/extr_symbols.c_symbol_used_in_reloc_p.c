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
struct TYPE_4__ {int sy_used_in_reloc; } ;
typedef  TYPE_1__ symbolS ;

/* Variables and functions */
 scalar_t__ LOCAL_SYMBOL_CHECK (TYPE_1__*) ; 

int
symbol_used_in_reloc_p (symbolS *s)
{
  if (LOCAL_SYMBOL_CHECK (s))
    return 0;
  return s->sy_used_in_reloc;
}