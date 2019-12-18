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
struct TYPE_2__ {void* userdata; int /*<<< orphan*/  cb; } ;
typedef  int /*<<< orphan*/  MMAL_POOL_T ;
typedef  TYPE_1__ MMAL_POOL_PRIVATE_T ;
typedef  int /*<<< orphan*/  MMAL_POOL_BH_CB_T ;

/* Variables and functions */

void mmal_pool_callback_set(MMAL_POOL_T *pool, MMAL_POOL_BH_CB_T cb, void *userdata)
{
   MMAL_POOL_PRIVATE_T *private = (MMAL_POOL_PRIVATE_T *)pool;
   private->cb = cb;
   private->userdata = userdata;
}