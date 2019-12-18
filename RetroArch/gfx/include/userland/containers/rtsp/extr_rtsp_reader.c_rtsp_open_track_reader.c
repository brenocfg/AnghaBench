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
typedef  scalar_t__ uint32_t ;
struct TYPE_3__ {int /*<<< orphan*/  reader; int /*<<< orphan*/  reader_uri; } ;
typedef  TYPE_1__ VC_CONTAINER_TRACK_MODULE_T ;
typedef  int /*<<< orphan*/  VC_CONTAINER_T ;
typedef  int /*<<< orphan*/  VC_CONTAINER_STATUS_T ;

/* Variables and functions */
 int /*<<< orphan*/  LOG_ERROR (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  VC_CONTAINER_ERROR_OUT_OF_MEMORY ; 
 int /*<<< orphan*/  VC_CONTAINER_SUCCESS ; 
 int /*<<< orphan*/  free (char*) ; 
 scalar_t__ malloc (scalar_t__) ; 
 int /*<<< orphan*/  vc_container_open_reader (char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vc_uri_build (int /*<<< orphan*/ ,char*,scalar_t__) ; 

__attribute__((used)) static VC_CONTAINER_STATUS_T rtsp_open_track_reader( VC_CONTAINER_T *p_ctx,
      VC_CONTAINER_TRACK_MODULE_T *t_module )
{
   VC_CONTAINER_STATUS_T status = VC_CONTAINER_SUCCESS;
   uint32_t uri_buffer_size;
   char *uri_buffer;

   uri_buffer_size = vc_uri_build(t_module->reader_uri, NULL, 0) + 1;
   uri_buffer = (char *)malloc(uri_buffer_size);
   if (!uri_buffer)
   {
      LOG_ERROR(p_ctx, "RTSP: Failed to build RTP URI");
      return VC_CONTAINER_ERROR_OUT_OF_MEMORY;
   }
   vc_uri_build(t_module->reader_uri, uri_buffer, uri_buffer_size);

   t_module->reader = vc_container_open_reader(uri_buffer, &status, NULL, NULL);
   free(uri_buffer);

   return status;
}