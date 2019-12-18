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
struct TYPE_4__ {scalar_t__ handle; scalar_t__ ctx; struct TYPE_4__* res_buf; struct TYPE_4__* buffers; int /*<<< orphan*/  num_buffers; int /*<<< orphan*/  source; } ;
typedef  TYPE_1__ al_t ;

/* Variables and functions */
 int /*<<< orphan*/  alDeleteBuffers (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  alDeleteSources (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  alSourceStop (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  alcCloseDevice (scalar_t__) ; 
 int /*<<< orphan*/  alcDestroyContext (scalar_t__) ; 
 int /*<<< orphan*/  alcMakeContextCurrent (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (TYPE_1__*) ; 

__attribute__((used)) static void al_free(void *data)
{
   al_t *al = (al_t*)data;

   if (!al)
      return;

   alSourceStop(al->source);
   alDeleteSources(1, &al->source);

   if (al->buffers)
      alDeleteBuffers(al->num_buffers, al->buffers);

   free(al->buffers);
   free(al->res_buf);
   alcMakeContextCurrent(NULL);

   if (al->ctx)
      alcDestroyContext(al->ctx);
   if (al->handle)
      alcCloseDevice(al->handle);
   free(al);
}