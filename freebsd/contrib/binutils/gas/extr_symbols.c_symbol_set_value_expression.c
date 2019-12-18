#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  sy_value; } ;
typedef  TYPE_1__ symbolS ;
struct local_symbol {int dummy; } ;
typedef  int /*<<< orphan*/  expressionS ;

/* Variables and functions */
 scalar_t__ LOCAL_SYMBOL_CHECK (TYPE_1__*) ; 
 int /*<<< orphan*/  S_CLEAR_WEAKREFR (TYPE_1__*) ; 
 TYPE_1__* local_symbol_convert (struct local_symbol*) ; 

void
symbol_set_value_expression (symbolS *s, const expressionS *exp)
{
  if (LOCAL_SYMBOL_CHECK (s))
    s = local_symbol_convert ((struct local_symbol *) s);
  s->sy_value = *exp;
  S_CLEAR_WEAKREFR (s);
}