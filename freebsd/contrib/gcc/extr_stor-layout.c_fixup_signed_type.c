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
 int HOST_BITS_PER_WIDE_INT ; 
 int TYPE_PRECISION (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  layout_type (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_min_and_max_values_for_integral_type (int /*<<< orphan*/ ,int,int) ; 

void
fixup_signed_type (tree type)
{
  int precision = TYPE_PRECISION (type);

  /* We can not represent properly constants greater then
     2 * HOST_BITS_PER_WIDE_INT, still we need the types
     as they are used by i386 vector extensions and friends.  */
  if (precision > HOST_BITS_PER_WIDE_INT * 2)
    precision = HOST_BITS_PER_WIDE_INT * 2;

  set_min_and_max_values_for_integral_type (type, precision,
					    /*is_unsigned=*/false);

  /* Lay out the type: set its alignment, size, etc.  */
  layout_type (type);
}