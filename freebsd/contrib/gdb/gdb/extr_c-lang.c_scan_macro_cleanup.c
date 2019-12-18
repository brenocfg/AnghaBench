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
 int /*<<< orphan*/  finished_macro_expansion () ; 
 scalar_t__ macro_original_text ; 

__attribute__((used)) static void
scan_macro_cleanup (void *dummy)
{
  if (macro_original_text)
    finished_macro_expansion ();
}