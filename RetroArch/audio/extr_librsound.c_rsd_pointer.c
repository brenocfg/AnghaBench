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
typedef  int /*<<< orphan*/  rsound_t ;

/* Variables and functions */
 int /*<<< orphan*/  retro_assert (int /*<<< orphan*/ ) ; 
 int rsnd_get_ptr (int /*<<< orphan*/ *) ; 

size_t rsd_pointer(rsound_t *rsound)
{
   retro_assert(rsound != NULL);
   int ptr;

   ptr = rsnd_get_ptr(rsound);

   return ptr;
}