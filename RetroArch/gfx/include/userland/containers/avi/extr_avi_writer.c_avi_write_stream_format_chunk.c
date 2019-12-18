#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
struct TYPE_5__ {TYPE_2__* format; } ;
typedef  TYPE_1__ VC_CONTAINER_TRACK_T ;
typedef  int /*<<< orphan*/  VC_CONTAINER_T ;
typedef  scalar_t__ VC_CONTAINER_STATUS_T ;
struct TYPE_6__ {scalar_t__ es_type; } ;

/* Variables and functions */
 int /*<<< orphan*/  AVI_END_CHUNK (int /*<<< orphan*/ *) ; 
 scalar_t__ STREAM_STATUS (int /*<<< orphan*/ *) ; 
 scalar_t__ VC_CONTAINER_ES_TYPE_AUDIO ; 
 scalar_t__ VC_CONTAINER_ES_TYPE_VIDEO ; 
 scalar_t__ VC_CONTAINER_SUCCESS ; 
 int /*<<< orphan*/  VC_FOURCC (char,char,char,float) ; 
 int /*<<< orphan*/  WRITE_FOURCC (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  WRITE_U32 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 scalar_t__ vc_container_write_bitmapinfoheader (int /*<<< orphan*/ *,TYPE_2__*) ; 
 scalar_t__ vc_container_write_waveformatex (int /*<<< orphan*/ *,TYPE_2__*) ; 

__attribute__((used)) static VC_CONTAINER_STATUS_T avi_write_stream_format_chunk(VC_CONTAINER_T *p_ctx,
   VC_CONTAINER_TRACK_T *track, uint32_t chunk_size)
{
   VC_CONTAINER_STATUS_T status;

   WRITE_FOURCC(p_ctx, VC_FOURCC('s','t','r','f'), "Chunk ID");
   WRITE_U32(p_ctx, chunk_size, "Chunk Size");

   if ((status = STREAM_STATUS(p_ctx)) != VC_CONTAINER_SUCCESS) return status;

   if(track->format->es_type == VC_CONTAINER_ES_TYPE_VIDEO)
      status = vc_container_write_bitmapinfoheader(p_ctx, track->format);
   else if(track->format->es_type == VC_CONTAINER_ES_TYPE_AUDIO)
      status = vc_container_write_waveformatex(p_ctx, track->format);

   if (status != VC_CONTAINER_SUCCESS) return status;

   AVI_END_CHUNK(p_ctx);

   return STREAM_STATUS(p_ctx);
}