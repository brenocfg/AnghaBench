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
struct TYPE_3__ {int /*<<< orphan*/  lock; int /*<<< orphan*/  usecount; int /*<<< orphan*/  service; } ;
typedef  int /*<<< orphan*/  MMAL_STATUS_T ;
typedef  TYPE_1__ MMAL_CLIENT_T ;

/* Variables and functions */
 int /*<<< orphan*/  MMAL_EIO ; 
 int /*<<< orphan*/  MMAL_SUCCESS ; 
 scalar_t__ VCHIQ_SUCCESS ; 
 scalar_t__ vchiq_use_service (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vcos_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vcos_mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static MMAL_STATUS_T mmal_vc_use_internal(MMAL_CLIENT_T *client)
{
   MMAL_STATUS_T status = MMAL_SUCCESS;
   vcos_mutex_lock(&client->lock);
   if(client->usecount++ == 0)
   {
      if(vchiq_use_service(client->service) != VCHIQ_SUCCESS)
      {
         client->usecount--;
         status = MMAL_EIO;
      }
   }
   vcos_mutex_unlock(&client->lock);
   return status;
}