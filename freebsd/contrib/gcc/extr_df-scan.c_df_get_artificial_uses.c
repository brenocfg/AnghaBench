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
struct df_ref {int dummy; } ;
struct df {struct dataflow** problems_by_index; } ;
struct dataflow {int dummy; } ;
struct TYPE_2__ {struct df_ref* artificial_uses; } ;

/* Variables and functions */
 size_t DF_SCAN ; 
 TYPE_1__* df_scan_get_bb_info (struct dataflow*,unsigned int) ; 

struct df_ref *
df_get_artificial_uses (struct df *df, unsigned int bb_index)
{
  struct dataflow *dflow = df->problems_by_index[DF_SCAN];
  return df_scan_get_bb_info (dflow, bb_index)->artificial_uses;
}