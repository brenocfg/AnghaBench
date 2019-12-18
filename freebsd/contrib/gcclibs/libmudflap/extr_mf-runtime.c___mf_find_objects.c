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
typedef  int /*<<< orphan*/  __mf_object_t ;

/* Variables and functions */
 int __MF_TYPE_GUESS ; 
 int __MF_TYPE_NOACCESS ; 
 unsigned int __mf_find_objects2 (uintptr_t,uintptr_t,int /*<<< orphan*/ **,unsigned int,int) ; 

unsigned
__mf_find_objects (uintptr_t ptr_low, uintptr_t ptr_high,
                   __mf_object_t **objs, unsigned max_objs)
{
  int type;
  unsigned count = 0;

  /* Search each splay tree for overlaps.  */
  for (type = __MF_TYPE_NOACCESS; type <= __MF_TYPE_GUESS; type++)
    {
      unsigned c = __mf_find_objects2 (ptr_low, ptr_high, objs, max_objs, type);
      if (c > max_objs)
        {
          max_objs = 0;
          objs = NULL;
        }
      else /* NB: C may equal 0 */
        {
          max_objs -= c;
          objs += c;
        }
      count += c;
    }

  return count;
}