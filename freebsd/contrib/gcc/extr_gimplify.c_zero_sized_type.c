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
 scalar_t__ AGGREGATE_TYPE_P (int /*<<< orphan*/ ) ; 
 scalar_t__ TYPE_SIZE (int /*<<< orphan*/ ) ; 
 scalar_t__ integer_zerop (scalar_t__) ; 

__attribute__((used)) static bool
zero_sized_type (tree type)
{
  if (AGGREGATE_TYPE_P (type) && TYPE_SIZE (type)
      && integer_zerop (TYPE_SIZE (type)))
    return true;
  return false;
}