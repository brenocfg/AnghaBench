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
struct floatformat {int dummy; } ;

/* Variables and functions */
 scalar_t__ TYPE_CODE (struct type const*) ; 
 scalar_t__ TYPE_CODE_FLT ; 
 struct floatformat const* TYPE_FLOATFORMAT (struct type const*) ; 
 int /*<<< orphan*/  TYPE_LENGTH (struct type const*) ; 
 struct floatformat const* floatformat_from_length (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gdb_assert (int) ; 

const struct floatformat *
floatformat_from_type (const struct type *type)
{
  gdb_assert (TYPE_CODE (type) == TYPE_CODE_FLT);
  if (TYPE_FLOATFORMAT (type) != NULL)
    return TYPE_FLOATFORMAT (type);
  else
    return floatformat_from_length (TYPE_LENGTH (type));
}