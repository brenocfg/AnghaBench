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
struct TYPE_3__ {int x; int y; scalar_t__ h; scalar_t__ w; } ;
struct TYPE_4__ {int /*<<< orphan*/  pitch; TYPE_1__ viewport; int /*<<< orphan*/  data; } ;

/* Variables and functions */
 int SYSTEM_MCD ; 
 int SYSTEM_MD ; 
 int SYSTEM_PBC ; 
 int /*<<< orphan*/  audio_batch_cb (int /*<<< orphan*/ ,int) ; 
 int audio_update (int /*<<< orphan*/ ) ; 
 TYPE_2__ bitmap ; 
 int /*<<< orphan*/  soundbuffer ; 
 int /*<<< orphan*/  system_frame_gen (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  system_frame_scd (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  system_frame_sms (int /*<<< orphan*/ ) ; 
 int system_hw ; 
 int /*<<< orphan*/  video_cb (int /*<<< orphan*/ ,scalar_t__,scalar_t__,int /*<<< orphan*/ ) ; 

void retro_run(void) 
{
   int aud;

   if (system_hw == SYSTEM_MCD)
      system_frame_scd(0);
   else if ((system_hw & SYSTEM_PBC) == SYSTEM_MD)
      system_frame_gen(0);
   else
      system_frame_sms(0);

   video_cb(bitmap.data, bitmap.viewport.w + (bitmap.viewport.x * 2), bitmap.viewport.h + (bitmap.viewport.y * 2), bitmap.pitch);

   aud = audio_update(soundbuffer) << 1;
   audio_batch_cb(soundbuffer, aud >> 1);
}