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
struct TYPE_3__ {size_t frame_size; int /*<<< orphan*/  renderer; } ;
typedef  TYPE_1__ wasapi_t ;
typedef  size_t UINT32 ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  int /*<<< orphan*/  BYTE ;

/* Variables and functions */
 scalar_t__ FAILED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _IAudioRenderClient_GetBuffer (int /*<<< orphan*/ ,size_t,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  _IAudioRenderClient_ReleaseBuffer (int /*<<< orphan*/ ,size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,void const*,size_t) ; 

__attribute__((used)) static bool wasapi_flush(wasapi_t * w, const void * data, size_t size)
{
   BYTE *dest         = NULL;
   UINT32 frame_count = size / w->frame_size;
   HRESULT hr         = _IAudioRenderClient_GetBuffer(
         w->renderer, frame_count, &dest);
   if (FAILED(hr))
      return false;

   memcpy(dest, data, size);
   hr = _IAudioRenderClient_ReleaseBuffer(
         w->renderer, frame_count,
         0);
   if (FAILED(hr))
      return false;

   return true;
}