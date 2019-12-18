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
struct df_ref_info {unsigned int refs_size; scalar_t__ refs; } ;
struct df_ref {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  memset (scalar_t__,int /*<<< orphan*/ ,unsigned int) ; 
 scalar_t__ xrealloc (scalar_t__,unsigned int) ; 

__attribute__((used)) static void 
df_grow_ref_info (struct df_ref_info *ref_info, unsigned int new_size)
{
  if (ref_info->refs_size < new_size)
    {
      ref_info->refs = xrealloc (ref_info->refs, 
				 new_size *sizeof (struct df_ref *));
      memset (ref_info->refs + ref_info->refs_size, 0,
	      (new_size - ref_info->refs_size) *sizeof (struct df_ref *));
      ref_info->refs_size = new_size;
    }
}