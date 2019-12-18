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
typedef  scalar_t__ u8 ;
typedef  int u32 ;
struct TYPE_3__ {scalar_t__ empty_framebuffer; } ;
typedef  TYPE_1__ ctr_video_t ;
struct TYPE_4__ {scalar_t__ frameBuffer; } ;
typedef  TYPE_2__ PrintConsole ;
typedef  int /*<<< orphan*/  Handle ;

/* Variables and functions */
 int /*<<< orphan*/  CFGU_GetModelNintendo2DS (scalar_t__*) ; 
 int ctr_bottom_screen_enabled ; 
 int* getThreadCommandBuffer () ; 
 scalar_t__** gfxBottomFramebuffers ; 
 scalar_t__ srvGetServiceHandle (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  svcCloseHandle (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svcSendSyncRequest (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ctr_set_bottom_screen_enable(void* data, bool enabled)
{
   Handle lcd_handle;
   u8 not_2DS;
   extern PrintConsole* currentConsole;
   ctr_video_t *ctr = (ctr_video_t*)data;

    if (!ctr)
      return;

   gfxBottomFramebuffers[0] = enabled ? (u8*)currentConsole->frameBuffer:
                                        (u8*)ctr->empty_framebuffer;

   CFGU_GetModelNintendo2DS(&not_2DS);
   if(not_2DS && srvGetServiceHandle(&lcd_handle, "gsp::Lcd") >= 0)
   {
      u32 *cmdbuf = getThreadCommandBuffer();
      cmdbuf[0] = enabled? 0x00110040:  0x00120040;
      cmdbuf[1] = 2;
      svcSendSyncRequest(lcd_handle);
      svcCloseHandle(lcd_handle);
   }

   ctr_bottom_screen_enabled = enabled;
}