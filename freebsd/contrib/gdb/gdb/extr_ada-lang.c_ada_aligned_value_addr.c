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
 int TARGET_CHAR_BIT ; 
 int TYPE_FIELD_BITPOS (struct type*,int /*<<< orphan*/ ) ; 
 struct type* TYPE_FIELD_TYPE (struct type*,int /*<<< orphan*/ ) ; 
 scalar_t__ ada_is_aligner_type (struct type*) ; 

char *
ada_aligned_value_addr (struct type *type, char *valaddr)
{
  if (ada_is_aligner_type (type))
    return ada_aligned_value_addr (TYPE_FIELD_TYPE (type, 0),
				   valaddr +
				   TYPE_FIELD_BITPOS (type,
						      0) / TARGET_CHAR_BIT);
  else
    return valaddr;
}