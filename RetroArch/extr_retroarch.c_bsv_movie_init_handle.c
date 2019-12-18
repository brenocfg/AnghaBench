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
typedef  enum rarch_movie_type { ____Placeholder_rarch_movie_type } rarch_movie_type ;
typedef  int /*<<< orphan*/  bsv_movie_t ;

/* Variables and functions */
 int /*<<< orphan*/ * bsv_movie_init_internal (char const*,int) ; 
 int /*<<< orphan*/ * bsv_movie_state_handle ; 

__attribute__((used)) static bool bsv_movie_init_handle(const char *path,
      enum rarch_movie_type type)
{
   bsv_movie_t *state     = bsv_movie_init_internal(path, type);
   if (!state)
      return false;

   bsv_movie_state_handle = state;
   return true;
}