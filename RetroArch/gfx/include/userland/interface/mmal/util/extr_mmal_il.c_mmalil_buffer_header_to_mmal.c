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
struct TYPE_6__ {int /*<<< orphan*/  flags; void* pts; void* dts; int /*<<< orphan*/  offset; int /*<<< orphan*/  length; int /*<<< orphan*/  alloc_size; int /*<<< orphan*/  data; scalar_t__ cmd; } ;
struct TYPE_5__ {int nFlags; int /*<<< orphan*/  nTimeStamp; int /*<<< orphan*/  nOffset; int /*<<< orphan*/  nFilledLen; int /*<<< orphan*/  nAllocLen; int /*<<< orphan*/  pBuffer; } ;
typedef  TYPE_1__ OMX_BUFFERHEADERTYPE ;
typedef  TYPE_2__ MMAL_BUFFER_HEADER_T ;

/* Variables and functions */
 void* MMAL_TIME_UNKNOWN ; 
 int OMX_BUFFERFLAG_TIME_IS_DTS ; 
 int OMX_BUFFERFLAG_TIME_UNKNOWN ; 
 int /*<<< orphan*/  mmalil_buffer_flags_to_mmal (int) ; 
 void* omx_ticks_to_s64 (int /*<<< orphan*/ ) ; 

void mmalil_buffer_header_to_mmal(MMAL_BUFFER_HEADER_T *mmal, OMX_BUFFERHEADERTYPE *omx)
{
   mmal->cmd = 0;
   mmal->data = omx->pBuffer;
   mmal->alloc_size = omx->nAllocLen;
   mmal->length = omx->nFilledLen;
   mmal->offset = omx->nOffset;
   if (omx->nFlags & OMX_BUFFERFLAG_TIME_IS_DTS)
   {
     mmal->dts = omx_ticks_to_s64(omx->nTimeStamp);
     mmal->pts = MMAL_TIME_UNKNOWN;
   }
   else if (omx->nFlags & OMX_BUFFERFLAG_TIME_UNKNOWN)
   {
     mmal->dts = MMAL_TIME_UNKNOWN;
     mmal->pts = MMAL_TIME_UNKNOWN;
   }
   else
   {
     mmal->dts = MMAL_TIME_UNKNOWN;
     mmal->pts = omx_ticks_to_s64(omx->nTimeStamp);
   }
   mmal->flags = mmalil_buffer_flags_to_mmal(omx->nFlags);
}