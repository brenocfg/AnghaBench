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
typedef  scalar_t__ diagnostic_t ;
struct TYPE_3__ {scalar_t__* classify_diagnostic; } ;
typedef  TYPE_1__ diagnostic_context ;

/* Variables and functions */
 scalar_t__ DK_LAST_DIAGNOSTIC_KIND ; 
 scalar_t__ DK_UNSPECIFIED ; 
 int N_OPTS ; 

diagnostic_t
diagnostic_classify_diagnostic (diagnostic_context *context,
				int option_index,
				diagnostic_t new_kind)
{
  diagnostic_t old_kind;

  if (option_index <= 0
      || option_index >= N_OPTS
      || new_kind >= DK_LAST_DIAGNOSTIC_KIND)
    return DK_UNSPECIFIED;

  old_kind = context->classify_diagnostic[option_index];
  context->classify_diagnostic[option_index] = new_kind;
  return old_kind;
}