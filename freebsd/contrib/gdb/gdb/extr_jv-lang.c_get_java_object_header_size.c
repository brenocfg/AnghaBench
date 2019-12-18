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
 int TARGET_PTR_BIT ; 
 int TYPE_LENGTH (struct type*) ; 
 struct type* get_java_object_type () ; 

int
get_java_object_header_size (void)
{
  struct type *objtype = get_java_object_type ();
  if (objtype == NULL)
    return (2 * TARGET_PTR_BIT / TARGET_CHAR_BIT);
  else
    return TYPE_LENGTH (objtype);
}