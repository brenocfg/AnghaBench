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
 scalar_t__ CLASSTYPE_HAS_MUTABLE (int /*<<< orphan*/ ) ; 
 scalar_t__ CLASS_TYPE_P (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strip_array_types (int /*<<< orphan*/ ) ; 

bool
cp_has_mutable_p (tree type)
{
  type = strip_array_types (type);

  return CLASS_TYPE_P (type) && CLASSTYPE_HAS_MUTABLE (type);
}