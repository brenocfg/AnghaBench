#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int when; int transform; int /*<<< orphan*/ * name; } ;

/* Variables and functions */
 int TRANSFORM_R ; 
 int TRANSFORM_W ; 
 unsigned int TTABLE_SIZE ; 
 int read_transforms ; 
 int rw_transforms ; 
 TYPE_1__* transform_info ; 
 int write_transforms ; 

__attribute__((used)) static void
validate_T(void)
   /* Validate the above table - this just builds the above values */
{
   unsigned int i;

   for (i=0; i<TTABLE_SIZE; ++i) if (transform_info[i].name != NULL)
   {
      if (transform_info[i].when & TRANSFORM_R)
         read_transforms |= transform_info[i].transform;

      if (transform_info[i].when & TRANSFORM_W)
         write_transforms |= transform_info[i].transform;
   }

   /* Reversible transforms are those which are supported on both read and
    * write.
    */
   rw_transforms = read_transforms & write_transforms;
}