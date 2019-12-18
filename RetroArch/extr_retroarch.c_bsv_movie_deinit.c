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
 int /*<<< orphan*/  bsv_movie_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * bsv_movie_state_handle ; 

__attribute__((used)) static void bsv_movie_deinit(void)
{
   if (!bsv_movie_state_handle)
      return;

   bsv_movie_free(bsv_movie_state_handle);
   bsv_movie_state_handle = NULL;
}