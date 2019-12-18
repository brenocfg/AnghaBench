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
typedef  int /*<<< orphan*/  MMAL_OPAQUE_IMAGE_HANDLE_T ;

/* Variables and functions */
 int /*<<< orphan*/  mmal_vc_opaque_alloc_desc (char*) ; 

MMAL_OPAQUE_IMAGE_HANDLE_T mmal_vc_opaque_alloc(void)
{
   return mmal_vc_opaque_alloc_desc("?");
}