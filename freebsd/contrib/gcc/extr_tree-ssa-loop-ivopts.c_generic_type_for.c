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
typedef  int /*<<< orphan*/  tree ;

/* Variables and functions */
 scalar_t__ POINTER_TYPE_P (int /*<<< orphan*/ ) ; 
 scalar_t__ TYPE_UNSIGNED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  unsigned_type_for (int /*<<< orphan*/ ) ; 

__attribute__((used)) static tree
generic_type_for (tree type)
{
  if (POINTER_TYPE_P (type))
    return unsigned_type_for (type);

  if (TYPE_UNSIGNED (type))
    return type;

  return unsigned_type_for (type);
}