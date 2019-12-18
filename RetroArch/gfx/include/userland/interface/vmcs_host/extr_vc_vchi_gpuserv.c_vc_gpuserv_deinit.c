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
struct TYPE_2__ {scalar_t__ refcount; int /*<<< orphan*/  lock; scalar_t__ service; } ;

/* Variables and functions */
 TYPE_1__ gpuserv_client ; 
 int /*<<< orphan*/  vchi_service_close (scalar_t__) ; 
 int /*<<< orphan*/  vcos_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vcos_mutex_unlock (int /*<<< orphan*/ *) ; 

void vc_gpuserv_deinit( void )
{
   vcos_mutex_lock(&gpuserv_client.lock);

   if (gpuserv_client.refcount > 0 && --gpuserv_client.refcount == 0)
   {
      vchi_service_close(gpuserv_client.service);
      gpuserv_client.service = 0;
   }
   vcos_mutex_unlock(&gpuserv_client.lock);
}