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
 struct type* TYPE_FIELD_TYPE (struct type*,int /*<<< orphan*/ ) ; 
 struct type* ada_get_base_type (struct type*) ; 
 scalar_t__ ada_is_aligner_type (struct type*) ; 

struct type *
ada_aligned_type (struct type *type)
{
  if (ada_is_aligner_type (type))
    return ada_aligned_type (TYPE_FIELD_TYPE (type, 0));
  else
    return ada_get_base_type (type);
}