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
struct df {scalar_t__* problems_by_index; } ;
typedef  int /*<<< orphan*/  bitmap ;
typedef  int /*<<< orphan*/  basic_block ;

/* Variables and functions */
 int /*<<< orphan*/  DF_LIVE_IN (struct df*,int /*<<< orphan*/ ) ; 
 size_t DF_LR ; 
 int /*<<< orphan*/  DF_RA_LIVE_IN (struct df*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DF_UPWARD_LIVE_IN (struct df*,int /*<<< orphan*/ ) ; 
 size_t DF_UR ; 
 size_t DF_UREC ; 
 int /*<<< orphan*/  gcc_assert (scalar_t__) ; 

bitmap
df_get_live_in (struct df *df, basic_block bb)
{
  gcc_assert (df->problems_by_index[DF_LR]);

  if (df->problems_by_index[DF_UREC])
    return DF_RA_LIVE_IN (df, bb);
  else if (df->problems_by_index[DF_UR])
    return DF_LIVE_IN (df, bb);
  else 
    return DF_UPWARD_LIVE_IN (df, bb);
}