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
struct type {int dummy; } ;

/* Variables and functions */
 scalar_t__ is_float_or_hfa_type_recurse (struct type*,struct type**) ; 

__attribute__((used)) static struct type *
is_float_or_hfa_type (struct type *t)
{
  struct type *et = 0;

  return is_float_or_hfa_type_recurse (t, &et) ? et : 0;
}