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
struct TYPE_3__ {int /*<<< orphan*/  buffer_r; int /*<<< orphan*/  buffer_l; int /*<<< orphan*/  mvoice; } ;
typedef  TYPE_1__ ax_audio_t ;

/* Variables and functions */
 int /*<<< orphan*/  AXFreeMultiVoice (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AXQuit () ; 
 int /*<<< orphan*/  AXRegisterFrameCallback (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  MEM1_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (TYPE_1__*) ; 
 int /*<<< orphan*/ * wiiu_cb_ax ; 

__attribute__((used)) static void ax_audio_free(void* data)
{
   ax_audio_t* ax = (ax_audio_t*)data;
   wiiu_cb_ax     = NULL;

   AXRegisterFrameCallback(NULL);
   AXFreeMultiVoice(ax->mvoice);
   AXQuit();

   MEM1_free(ax->buffer_l);
   MEM1_free(ax->buffer_r);
   free(ax);
}