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

/* Variables and functions */
 int /*<<< orphan*/ * bivs ; 
 int /*<<< orphan*/  clear_iv_info () ; 
 int /*<<< orphan*/ * df ; 
 int /*<<< orphan*/  df_finish (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  htab_delete (int /*<<< orphan*/ *) ; 

void
iv_analysis_done (void)
{
  if (df)
    {
      clear_iv_info ();
      df_finish (df);
      df = NULL;
      htab_delete (bivs);
      bivs = NULL;
    }
}