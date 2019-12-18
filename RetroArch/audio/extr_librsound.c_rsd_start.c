#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ rate; scalar_t__ channels; int /*<<< orphan*/ * port; int /*<<< orphan*/ * host; } ;
typedef  TYPE_1__ rsound_t ;

/* Variables and functions */
 int /*<<< orphan*/  retro_assert (int) ; 
 scalar_t__ rsnd_create_connection (TYPE_1__*) ; 

int rsd_start(rsound_t *rsound)
{
   retro_assert(rsound != NULL);
   retro_assert(rsound->rate > 0);
   retro_assert(rsound->channels > 0);
   retro_assert(rsound->host != NULL);
   retro_assert(rsound->port != NULL);

   if ( rsnd_create_connection(rsound) < 0 )
      return -1;

   return 0;
}