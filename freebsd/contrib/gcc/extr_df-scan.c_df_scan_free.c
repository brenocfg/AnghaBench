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
struct df {scalar_t__ blocks_to_analyze; scalar_t__ blocks_to_scan; } ;
struct dataflow {struct dataflow* problem_data; struct df* df; } ;

/* Variables and functions */
 int /*<<< orphan*/  BITMAP_FREE (scalar_t__) ; 
 int /*<<< orphan*/  df_scan_free_internal (struct dataflow*) ; 
 int /*<<< orphan*/  free (struct dataflow*) ; 

__attribute__((used)) static void 
df_scan_free (struct dataflow *dflow)
{
  struct df *df = dflow->df;
  
  if (dflow->problem_data)
    {
      df_scan_free_internal (dflow);
      free (dflow->problem_data);
    }

  if (df->blocks_to_scan)
    BITMAP_FREE (df->blocks_to_scan);
  
  if (df->blocks_to_analyze)
    BITMAP_FREE (df->blocks_to_analyze);

  free (dflow);
}