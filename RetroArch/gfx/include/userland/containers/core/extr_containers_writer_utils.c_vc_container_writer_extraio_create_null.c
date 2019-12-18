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
typedef  int /*<<< orphan*/  VC_CONTAINER_WRITER_EXTRAIO_T ;
typedef  int /*<<< orphan*/  VC_CONTAINER_T ;
typedef  int /*<<< orphan*/  VC_CONTAINER_STATUS_T ;

/* Variables and functions */
 int /*<<< orphan*/  vc_container_writer_extraio_create (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *) ; 

VC_CONTAINER_STATUS_T vc_container_writer_extraio_create_null(VC_CONTAINER_T *context, VC_CONTAINER_WRITER_EXTRAIO_T *extraio)
{
   return vc_container_writer_extraio_create(context, "null://", extraio);
}