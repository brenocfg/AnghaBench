#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__ num_masks; scalar_t__ masks; } ;
struct TYPE_7__ {TYPE_1__ masks; } ;
struct TYPE_6__ {scalar_t__ end_point; } ;
typedef  TYPE_2__* PS_Mask ;
typedef  TYPE_3__* PS_Dimension ;
typedef  scalar_t__ FT_UInt ;

/* Variables and functions */

__attribute__((used)) static void
  ps_dimension_end_mask( PS_Dimension  dim,
                         FT_UInt       end_point )
  {
    FT_UInt  count = dim->masks.num_masks;
    PS_Mask  mask;


    if ( count > 0 )
    {
      mask            = dim->masks.masks + count - 1;
      mask->end_point = end_point;
    }
  }