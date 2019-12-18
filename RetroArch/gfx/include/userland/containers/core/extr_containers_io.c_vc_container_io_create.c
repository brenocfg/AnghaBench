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
typedef  int /*<<< orphan*/  VC_CONTAINER_STATUS_T ;
typedef  int /*<<< orphan*/  VC_CONTAINER_IO_T ;
typedef  int /*<<< orphan*/  VC_CONTAINER_IO_MODE_T ;
typedef  int /*<<< orphan*/  VC_CONTAINER_IO_CAPABILITIES_T ;

/* Variables and functions */
 int /*<<< orphan*/ * vc_container_io_open_core (char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 

VC_CONTAINER_IO_T *vc_container_io_create( const char *uri, VC_CONTAINER_IO_MODE_T mode,
                                           VC_CONTAINER_IO_CAPABILITIES_T capabilities,
                                           VC_CONTAINER_STATUS_T *p_status )
{
   return vc_container_io_open_core( uri, mode, capabilities, false, p_status );
}