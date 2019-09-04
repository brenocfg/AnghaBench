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
 int /*<<< orphan*/ * easysrc_clean ; 
 int /*<<< orphan*/ * easysrc_code ; 
 int /*<<< orphan*/ * easysrc_data ; 
 int /*<<< orphan*/ * easysrc_decl ; 
 int /*<<< orphan*/ * easysrc_toohard ; 
 int /*<<< orphan*/  slist_wc_free_all (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void easysrc_free(void)
{
  slist_wc_free_all(easysrc_decl);
  easysrc_decl = NULL;
  slist_wc_free_all(easysrc_data);
  easysrc_data = NULL;
  slist_wc_free_all(easysrc_code);
  easysrc_code = NULL;
  slist_wc_free_all(easysrc_toohard);
  easysrc_toohard = NULL;
  slist_wc_free_all(easysrc_clean);
  easysrc_clean = NULL;
}