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
 char* TYPE_NAME (struct type const*) ; 
 char* TYPE_TAG_NAME (struct type const*) ; 

char *
type_name_no_tag (const struct type *type)
{
  if (TYPE_TAG_NAME (type) != NULL)
    return TYPE_TAG_NAME (type);

  /* Is there code which expects this to return the name if there is no
     tag name?  My guess is that this is mainly used for C++ in cases where
     the two will always be the same.  */
  return TYPE_NAME (type);
}