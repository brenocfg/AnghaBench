#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
struct TYPE_9__ {int /*<<< orphan*/  audio_render; } ;
struct TYPE_7__ {int /*<<< orphan*/  nVersion; } ;
struct TYPE_8__ {int nSize; int nPortIndex; int /*<<< orphan*/  nU32; TYPE_1__ nVersion; } ;
typedef  TYPE_2__ OMX_PARAM_U32TYPE ;
typedef  scalar_t__ OMX_ERRORTYPE ;
typedef  TYPE_3__ AUDIOPLAY_STATE_T ;

/* Variables and functions */
 int /*<<< orphan*/  ILC_GET_HANDLE (int /*<<< orphan*/ ) ; 
 scalar_t__ OMX_ErrorNone ; 
 scalar_t__ OMX_GetConfig (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  OMX_IndexConfigAudioRenderingLatency ; 
 int /*<<< orphan*/  OMX_VERSION ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  memset (TYPE_2__*,int /*<<< orphan*/ ,int) ; 

uint32_t audioplay_get_latency(AUDIOPLAY_STATE_T *st)
{
   OMX_PARAM_U32TYPE param;
   OMX_ERRORTYPE error;

   memset(&param, 0, sizeof(OMX_PARAM_U32TYPE));
   param.nSize = sizeof(OMX_PARAM_U32TYPE);
   param.nVersion.nVersion = OMX_VERSION;
   param.nPortIndex = 100;

   error = OMX_GetConfig(ILC_GET_HANDLE(st->audio_render), OMX_IndexConfigAudioRenderingLatency, &param);
   assert(error == OMX_ErrorNone);

   return param.nU32;
}