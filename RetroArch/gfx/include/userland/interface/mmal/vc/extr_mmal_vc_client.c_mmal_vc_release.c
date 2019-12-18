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
struct TYPE_3__ {scalar_t__ inited; } ;
typedef  int /*<<< orphan*/  MMAL_STATUS_T ;

/* Variables and functions */
 int /*<<< orphan*/  MMAL_ENOTCONN ; 
 TYPE_1__ client ; 
 int /*<<< orphan*/  mmal_vc_release_internal (TYPE_1__*) ; 

MMAL_STATUS_T mmal_vc_release(void)
{
   MMAL_STATUS_T status = MMAL_ENOTCONN;
   if(client.inited)
      status = mmal_vc_release_internal(&client);
   return status;
}