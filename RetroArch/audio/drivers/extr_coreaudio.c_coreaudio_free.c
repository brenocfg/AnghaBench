#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  cond; int /*<<< orphan*/  lock; scalar_t__ buffer; int /*<<< orphan*/  dev; scalar_t__ dev_alive; } ;
typedef  TYPE_1__ coreaudio_t ;

/* Variables and functions */
 int /*<<< orphan*/  AudioComponentInstanceDispose (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AudioOutputUnitStop (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CloseComponent (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fifo_free (scalar_t__) ; 
 int /*<<< orphan*/  free (TYPE_1__*) ; 
 int /*<<< orphan*/  scond_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  slock_free (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void coreaudio_free(void *data)
{
   coreaudio_t *dev = (coreaudio_t*)data;

   if (!dev)
      return;

   if (dev->dev_alive)
   {
      AudioOutputUnitStop(dev->dev);
#if (defined(__MACH__) && (defined(__ppc__) || defined(__ppc64__)))
      CloseComponent(dev->dev);
#else
      AudioComponentInstanceDispose(dev->dev);
#endif
   }

   if (dev->buffer)
      fifo_free(dev->buffer);

   slock_free(dev->lock);
   scond_free(dev->cond);

   free(dev);
}