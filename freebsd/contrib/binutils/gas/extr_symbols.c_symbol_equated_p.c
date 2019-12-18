#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__ X_op; } ;
struct TYPE_6__ {TYPE_1__ sy_value; } ;
typedef  TYPE_2__ symbolS ;

/* Variables and functions */
 scalar_t__ LOCAL_SYMBOL_CHECK (TYPE_2__*) ; 
 scalar_t__ O_symbol ; 

int
symbol_equated_p (symbolS *s)
{
  if (LOCAL_SYMBOL_CHECK (s))
    return 0;
  return s->sy_value.X_op == O_symbol;
}