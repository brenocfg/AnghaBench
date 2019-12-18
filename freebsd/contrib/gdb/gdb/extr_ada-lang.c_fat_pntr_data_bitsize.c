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
 int TYPE_FIELD_BITSIZE (struct type*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TYPE_FIELD_TYPE (struct type*,int /*<<< orphan*/ ) ; 
 int TYPE_LENGTH (int /*<<< orphan*/ ) ; 
 struct type* desc_base_type (struct type*) ; 

__attribute__((used)) static int
fat_pntr_data_bitsize (struct type *type)
{
  type = desc_base_type (type);

  if (TYPE_FIELD_BITSIZE (type, 0) > 0)
    return TYPE_FIELD_BITSIZE (type, 0);
  else
    return TARGET_CHAR_BIT * TYPE_LENGTH (TYPE_FIELD_TYPE (type, 0));
}