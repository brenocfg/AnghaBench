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
 int /*<<< orphan*/  DECL_FIELD_BIT_OFFSET (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DECL_FIELD_OFFSET (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  byte_from_pos (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

tree
byte_position (tree field)
{
  return byte_from_pos (DECL_FIELD_OFFSET (field),
			DECL_FIELD_BIT_OFFSET (field));
}