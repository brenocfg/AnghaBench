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
 scalar_t__ VC_CONTAINER_SUCCESS ; 
 scalar_t__ rtsp_create_tracks_from_response (int /*<<< orphan*/ *) ; 
 scalar_t__ rtsp_read_response (int /*<<< orphan*/ *) ; 
 scalar_t__ rtsp_send_describe_request (int /*<<< orphan*/ *) ; 

__attribute__((used)) static VC_CONTAINER_STATUS_T rtsp_describe( VC_CONTAINER_T *p_ctx )
{
   VC_CONTAINER_STATUS_T status = VC_CONTAINER_SUCCESS;

   /* Send DESCRIBE request and get response */
   status = rtsp_send_describe_request(p_ctx);
   if (status != VC_CONTAINER_SUCCESS) return status;
   status = rtsp_read_response(p_ctx);
   if (status != VC_CONTAINER_SUCCESS) return status;

   /* Create tracks from SDP content */
   status = rtsp_create_tracks_from_response(p_ctx);

   return status;
}