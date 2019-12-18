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
 int TYPE_READONLY (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strip_array_types (int /*<<< orphan*/ ) ; 

bool
cp_type_readonly (tree type)
{
  type = strip_array_types (type);
  return TYPE_READONLY (type);
}