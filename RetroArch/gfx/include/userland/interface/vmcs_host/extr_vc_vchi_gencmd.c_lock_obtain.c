#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  lock; scalar_t__ initialised; } ;

/* Variables and functions */
 scalar_t__ VCOS_SUCCESS ; 
 TYPE_1__ gencmd_client ; 
 scalar_t__ vcos_mutex_lock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static __inline int lock_obtain (void) {
   int ret = -1;
   if(gencmd_client.initialised && vcos_mutex_lock(&gencmd_client.lock) == VCOS_SUCCESS)
   {
      ret = 0;
   }

   return ret;
}