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
typedef  int /*<<< orphan*/ * tree ;
typedef  enum escape_t { ____Placeholder_escape_t } escape_t ;
typedef  int /*<<< orphan*/ * bitmap ;

/* Variables and functions */
#define  EXPOSED_PARAMETER 129 
#define  FULL_ESCAPE 128 
 int TYPE_UID (int /*<<< orphan*/ *) ; 
 scalar_t__ bitmap_bit_p (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  bitmap_set_bit (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/ * get_canon_type (int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/ * global_types_exposed_parameter ; 
 int /*<<< orphan*/ * global_types_full_escape ; 

__attribute__((used)) static tree
mark_type (tree type, enum escape_t escape_status)
{
  bitmap map = NULL;
  int uid;

  type = get_canon_type (type, true, true);
  if (!type) 
    return NULL;

  switch (escape_status) 
    {
    case EXPOSED_PARAMETER:
      map = global_types_exposed_parameter;
      break;
    case FULL_ESCAPE:
      map = global_types_full_escape;
      break;
    }

  uid = TYPE_UID (type);
  if (bitmap_bit_p (map, uid))
    return type;
  else
    {
      bitmap_set_bit (map, uid);
      if (escape_status == FULL_ESCAPE)
	{
	  /* Efficiency hack. When things are bad, do not mess around
	     with this type anymore.  */
	  bitmap_set_bit (global_types_exposed_parameter, uid);
	}      
    }
  return type;
}