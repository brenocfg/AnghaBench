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
 int TYPE_FIELD_BITSIZE (struct type*,int) ; 
 int /*<<< orphan*/  TYPE_FIELD_TYPE (struct type*,int) ; 
 int TYPE_LENGTH (int /*<<< orphan*/ ) ; 
 struct type* desc_base_type (struct type*) ; 

__attribute__((used)) static int
desc_bound_bitsize (struct type *type, int i, int which)
{
  type = desc_base_type (type);

  if (TYPE_FIELD_BITSIZE (type, 2 * i + which - 2) > 0)
    return TYPE_FIELD_BITSIZE (type, 2 * i + which - 2);
  else
    return 8 * TYPE_LENGTH (TYPE_FIELD_TYPE (type, 2 * i + which - 2));
}