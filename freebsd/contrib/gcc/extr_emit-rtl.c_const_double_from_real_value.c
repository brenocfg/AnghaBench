#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_2__* rtx ;
typedef  enum machine_mode { ____Placeholder_machine_mode } machine_mode ;
struct TYPE_8__ {int /*<<< orphan*/  rv; } ;
struct TYPE_9__ {TYPE_1__ u; } ;
typedef  int /*<<< orphan*/  REAL_VALUE_TYPE ;

/* Variables and functions */
 int /*<<< orphan*/  CONST_DOUBLE ; 
 int /*<<< orphan*/  PUT_MODE (TYPE_2__*,int) ; 
 TYPE_2__* lookup_const_double (TYPE_2__*) ; 
 TYPE_2__* rtx_alloc (int /*<<< orphan*/ ) ; 

rtx
const_double_from_real_value (REAL_VALUE_TYPE value, enum machine_mode mode)
{
  rtx real = rtx_alloc (CONST_DOUBLE);
  PUT_MODE (real, mode);

  real->u.rv = value;

  return lookup_const_double (real);
}