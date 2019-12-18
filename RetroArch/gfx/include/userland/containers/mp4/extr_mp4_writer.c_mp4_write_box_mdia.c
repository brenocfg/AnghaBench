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
typedef  int /*<<< orphan*/  VC_CONTAINER_T ;
typedef  scalar_t__ VC_CONTAINER_STATUS_T ;

/* Variables and functions */
 int /*<<< orphan*/  MP4_BOX_TYPE_HDLR ; 
 int /*<<< orphan*/  MP4_BOX_TYPE_MDHD ; 
 int /*<<< orphan*/  MP4_BOX_TYPE_MINF ; 
 scalar_t__ VC_CONTAINER_SUCCESS ; 
 scalar_t__ mp4_write_box (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static VC_CONTAINER_STATUS_T mp4_write_box_mdia( VC_CONTAINER_T *p_ctx )
{
   VC_CONTAINER_STATUS_T status = VC_CONTAINER_SUCCESS;

   status = mp4_write_box(p_ctx, MP4_BOX_TYPE_MDHD);
   if(status != VC_CONTAINER_SUCCESS) return status;

   status = mp4_write_box(p_ctx, MP4_BOX_TYPE_HDLR);
   if(status != VC_CONTAINER_SUCCESS) return status;

   status = mp4_write_box(p_ctx, MP4_BOX_TYPE_MINF);
   if(status != VC_CONTAINER_SUCCESS) return status;

   return status;
}