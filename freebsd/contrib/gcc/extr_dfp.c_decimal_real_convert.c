#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct real_format {int b; } ;
typedef  enum machine_mode { ____Placeholder_machine_mode } machine_mode ;
struct TYPE_8__ {scalar_t__ decimal; } ;
typedef  TYPE_1__ REAL_VALUE_TYPE ;

/* Variables and functions */
 struct real_format* REAL_MODE_FORMAT (int) ; 
 int /*<<< orphan*/  decimal_from_binary (TYPE_1__*,TYPE_1__ const*) ; 
 int /*<<< orphan*/  decimal_to_binary (TYPE_1__*,TYPE_1__ const*,int) ; 

void
decimal_real_convert (REAL_VALUE_TYPE *r, enum machine_mode mode, 
		      const REAL_VALUE_TYPE *a)
{
  const struct real_format *fmt = REAL_MODE_FORMAT (mode);

  if (a->decimal && fmt->b == 10)
    return;
  if (a->decimal)
      decimal_to_binary (r, a, mode);
  else
      decimal_from_binary (r, a);
}