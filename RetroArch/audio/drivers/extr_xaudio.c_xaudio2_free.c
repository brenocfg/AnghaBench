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
struct TYPE_3__ {int /*<<< orphan*/  buf; scalar_t__ hEvent; scalar_t__ pXAudio2; scalar_t__ pMasterVoice; scalar_t__ pSourceVoice; } ;
typedef  TYPE_1__ xaudio2_t ;
typedef  int /*<<< orphan*/  delete ;

/* Variables and functions */
 int /*<<< orphan*/  CloseHandle (scalar_t__) ; 
 int /*<<< orphan*/  IXAudio2MasteringVoice_DestroyVoice (scalar_t__) ; 
 int /*<<< orphan*/  IXAudio2SourceVoice_DestroyVoice (scalar_t__) ; 
 int /*<<< orphan*/  IXAudio2SourceVoice_Stop (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IXAudio2_Release (scalar_t__) ; 
 int /*<<< orphan*/  XAUDIO2_COMMIT_NOW ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void xaudio2_free(xaudio2_t *handle)
{
   if (!handle)
      return;

   if (handle->pSourceVoice)
   {
      IXAudio2SourceVoice_Stop(handle->pSourceVoice,
            0, XAUDIO2_COMMIT_NOW);
      IXAudio2SourceVoice_DestroyVoice(handle->pSourceVoice);
   }

   if (handle->pMasterVoice)
   {
      IXAudio2MasteringVoice_DestroyVoice(handle->pMasterVoice);
   }

   if (handle->pXAudio2)
   {
      IXAudio2_Release(handle->pXAudio2);
   }

   if (handle->hEvent)
      CloseHandle(handle->hEvent);

   free(handle->buf);

#if defined(__cplusplus) && !defined(CINTERFACE)
   delete handle;
#else
   free(handle);
#endif
}