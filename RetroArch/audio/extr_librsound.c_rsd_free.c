#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  cond; int /*<<< orphan*/  cond_mutex; int /*<<< orphan*/  mutex; } ;
struct TYPE_6__ {TYPE_1__ thread; int /*<<< orphan*/  cb_lock; struct TYPE_6__* port; struct TYPE_6__* host; scalar_t__ fifo_buffer; } ;
typedef  TYPE_2__ rsound_t ;

/* Variables and functions */
 int /*<<< orphan*/  fifo_free (scalar_t__) ; 
 int /*<<< orphan*/  free (TYPE_2__*) ; 
 int /*<<< orphan*/  retro_assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  scond_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  slock_free (int /*<<< orphan*/ ) ; 

int rsd_free(rsound_t *rsound)
{
   retro_assert(rsound != NULL);
   if (rsound->fifo_buffer)
      fifo_free(rsound->fifo_buffer);
   if (rsound->host)
      free(rsound->host);
   if (rsound->port)
      free(rsound->port);

   slock_free(rsound->thread.mutex);
   slock_free(rsound->thread.cond_mutex);
   slock_free(rsound->cb_lock);
   scond_free(rsound->thread.cond);

   free(rsound);

   return 0;
}