#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct display {scalar_t__* value; } ;
typedef  size_t png_byte ;
struct TYPE_4__ {size_t value_count; TYPE_1__* values; } ;
struct TYPE_3__ {scalar_t__ name; scalar_t__ value; } ;

/* Variables and functions */
 scalar_t__ all ; 
 TYPE_2__* options ; 
 scalar_t__ range_hi ; 
 scalar_t__ range_lo ; 

__attribute__((used)) static int
opt_list_end(struct display *dp, png_byte opt, png_byte entry)
{
   if (options[opt].values[entry].name == range_lo)
      return entry+1U >= options[opt].value_count /* missing range_hi */ ||
         options[opt].values[entry+1U].name != range_hi /* likewise */ ||
         options[opt].values[entry+1U].value <= dp->value[opt] /* range end */;

   else
      return entry+1U >= options[opt].value_count /* missing 'all' */ ||
         options[opt].values[entry+1U].name == all /* last entry */;
}