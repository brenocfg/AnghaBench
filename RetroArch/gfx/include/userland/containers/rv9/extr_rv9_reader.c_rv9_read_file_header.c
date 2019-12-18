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
typedef  char uint8_t ;
typedef  int uint32_t ;
typedef  int /*<<< orphan*/  dummy ;
struct TYPE_6__ {TYPE_1__* format; } ;
typedef  TYPE_2__ VC_CONTAINER_TRACK_T ;
typedef  int /*<<< orphan*/  VC_CONTAINER_T ;
typedef  scalar_t__ VC_CONTAINER_STATUS_T ;
typedef  int /*<<< orphan*/  VC_CONTAINER_FOURCC_T ;
struct TYPE_5__ {int extradata_size; int /*<<< orphan*/  codec; int /*<<< orphan*/  extradata; } ;

/* Variables and functions */
 int BI32 (char*) ; 
 int PEEK_BYTES (int /*<<< orphan*/ *,char*,int) ; 
 int READ_BYTES (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 scalar_t__ STREAM_STATUS (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  VC_CONTAINER_CODEC_RV10 ; 
 int /*<<< orphan*/  VC_CONTAINER_CODEC_RV20 ; 
 int /*<<< orphan*/  VC_CONTAINER_CODEC_RV30 ; 
 int /*<<< orphan*/  VC_CONTAINER_CODEC_RV40 ; 
 scalar_t__ VC_CONTAINER_ERROR_EOS ; 
 scalar_t__ VC_CONTAINER_ERROR_FORMAT_NOT_SUPPORTED ; 
 scalar_t__ VC_CONTAINER_SUCCESS ; 
 scalar_t__ vc_container_track_allocate_extradata (int /*<<< orphan*/ *,TYPE_2__*,int) ; 

__attribute__((used)) static VC_CONTAINER_STATUS_T rv9_read_file_header(VC_CONTAINER_T *p_ctx,
   VC_CONTAINER_TRACK_T *track)
{
   VC_CONTAINER_STATUS_T status;
   VC_CONTAINER_FOURCC_T codec;
   uint8_t dummy[12];
   uint32_t length;

   if(PEEK_BYTES(p_ctx, dummy, sizeof(dummy)) != sizeof(dummy)) return VC_CONTAINER_ERROR_EOS;

   length = BI32(dummy);
   if(length < 12 || length > 1024) return VC_CONTAINER_ERROR_FORMAT_NOT_SUPPORTED;

   if(dummy[4] != 'V' || dummy[5] != 'I' || dummy[6] != 'D' || dummy[7] != 'O' ||
      dummy[8] != 'R' || dummy[9] != 'V' ||                    dummy[11] != '0')
      return VC_CONTAINER_ERROR_FORMAT_NOT_SUPPORTED;

   switch(dummy[10]) {
   case '4': codec = VC_CONTAINER_CODEC_RV40; break;
   case '3': codec = VC_CONTAINER_CODEC_RV30; break;
   case '2': codec = VC_CONTAINER_CODEC_RV20; break;
   case '1': codec = VC_CONTAINER_CODEC_RV10; break;
   default: return VC_CONTAINER_ERROR_FORMAT_NOT_SUPPORTED;
   }

   if (!track)
      return VC_CONTAINER_SUCCESS;

   status = vc_container_track_allocate_extradata(p_ctx, track, length);
   if(status != VC_CONTAINER_SUCCESS) return status;

   if(READ_BYTES(p_ctx, track->format->extradata, length) != length) return VC_CONTAINER_ERROR_EOS;
   track->format->extradata_size = length;

   track->format->codec = codec;
   return STREAM_STATUS(p_ctx);
}