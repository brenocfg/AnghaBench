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
 int /*<<< orphan*/  DF_USES_GET (int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  ddf ; 
 int /*<<< orphan*/  df_ref_debug (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stderr ; 

void
debug_df_useno (unsigned int defno)
{
  df_ref_debug (DF_USES_GET (ddf, defno), stderr);
}