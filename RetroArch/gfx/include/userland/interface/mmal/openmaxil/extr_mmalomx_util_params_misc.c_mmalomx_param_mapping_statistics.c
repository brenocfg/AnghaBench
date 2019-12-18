#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  corrupt_macroblocks; int /*<<< orphan*/  total_bytes; int /*<<< orphan*/  maximum_frame_bytes; int /*<<< orphan*/  eos_seen; int /*<<< orphan*/  frames_discarded; int /*<<< orphan*/  frames_skipped; scalar_t__ frame_count; int /*<<< orphan*/  buffer_count; } ;
struct TYPE_3__ {int /*<<< orphan*/  nCorruptMBs; int /*<<< orphan*/  nByteCount; int /*<<< orphan*/  nMaxFrameSize; int /*<<< orphan*/  nEOS; int /*<<< orphan*/  nDiscards; int /*<<< orphan*/  nFrameSkips; scalar_t__ nImageCount; scalar_t__ nFrameCount; int /*<<< orphan*/  nBufferCount; } ;
typedef  scalar_t__ OMX_PTR ;
typedef  TYPE_1__ OMX_CONFIG_BRCMPORTSTATSTYPE ;
typedef  int /*<<< orphan*/  MMAL_STATUS_T ;
typedef  TYPE_2__ MMAL_PARAMETER_STATISTICS_T ;
typedef  int /*<<< orphan*/  MMAL_PARAMETER_HEADER_T ;
typedef  scalar_t__ MMALOMX_PARAM_MAPPING_DIRECTION ;

/* Variables and functions */
 scalar_t__ MMALOMX_PARAM_MAPPING_TO_MMAL ; 
 int /*<<< orphan*/  MMAL_SUCCESS ; 
 int /*<<< orphan*/  omx_ticks_from_s64 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  omx_ticks_to_s64 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static MMAL_STATUS_T mmalomx_param_mapping_statistics(MMALOMX_PARAM_MAPPING_DIRECTION dir,
   MMAL_PARAMETER_HEADER_T *mmal_param, OMX_PTR omx_param)
{
   OMX_CONFIG_BRCMPORTSTATSTYPE *omx = (OMX_CONFIG_BRCMPORTSTATSTYPE *)omx_param;
   MMAL_PARAMETER_STATISTICS_T *mmal = (MMAL_PARAMETER_STATISTICS_T *)mmal_param;

   if (dir == MMALOMX_PARAM_MAPPING_TO_MMAL)
   {
      mmal->buffer_count        = omx->nBufferCount;
      mmal->frame_count         = omx->nImageCount + omx->nFrameCount;
      mmal->frames_skipped      = omx->nFrameSkips;
      mmal->frames_discarded    = omx->nDiscards;
      mmal->eos_seen            = omx->nEOS;
      mmal->maximum_frame_bytes = omx->nMaxFrameSize;
      mmal->total_bytes         = omx_ticks_to_s64(omx->nByteCount);
      mmal->corrupt_macroblocks = omx->nCorruptMBs;
   }
   else
   {
      omx->nBufferCount = mmal->buffer_count;
      omx->nFrameCount = mmal->frame_count;
      omx->nImageCount = 0;
      omx->nFrameSkips = mmal->frames_skipped;
      omx->nDiscards = mmal->frames_discarded;
      omx->nEOS = mmal->eos_seen;
      omx->nMaxFrameSize = mmal->maximum_frame_bytes;
      omx->nByteCount = omx_ticks_from_s64(mmal->total_bytes);
      omx->nCorruptMBs = mmal->corrupt_macroblocks;
   }

   return MMAL_SUCCESS;
}