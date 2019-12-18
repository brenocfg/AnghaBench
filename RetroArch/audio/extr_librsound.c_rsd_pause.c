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
 int rsd_start (int /*<<< orphan*/ *) ; 
 int rsd_stop (int /*<<< orphan*/ *) ; 

int rsd_pause(rsound_t* rsound, int enable)
{
   retro_assert(rsound != NULL);
   if ( enable )
      return rsd_stop(rsound);

   return rsd_start(rsound);
}