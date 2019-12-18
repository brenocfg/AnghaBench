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
typedef  int /*<<< orphan*/  int64_t ;
typedef  int /*<<< orphan*/  VC_CONTAINER_T ;
typedef  scalar_t__ VC_CONTAINER_STATUS_T ;
typedef  int /*<<< orphan*/  MP4_BOX_TYPE_T ;

/* Variables and functions */
 scalar_t__ VC_CONTAINER_SUCCESS ; 
 scalar_t__ mp4_read_box_data (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ mp4_read_box_header (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static VC_CONTAINER_STATUS_T mp4_read_box( VC_CONTAINER_T *p_ctx, int64_t size,
   MP4_BOX_TYPE_T parent_type )
{
   VC_CONTAINER_STATUS_T status;
   MP4_BOX_TYPE_T box_type;
   int64_t box_size;

   status = mp4_read_box_header( p_ctx, size, &box_type, &box_size );
   if(status != VC_CONTAINER_SUCCESS) return status;
   return mp4_read_box_data( p_ctx, box_type, box_size, parent_type );
}