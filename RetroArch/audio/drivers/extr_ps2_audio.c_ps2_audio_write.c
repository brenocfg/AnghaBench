#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int ssize_t ;
struct TYPE_2__ {int /*<<< orphan*/  running; } ;
typedef  TYPE_1__ ps2_audio_t ;

/* Variables and functions */
 int audsrv_play_audio (void const*,size_t) ; 

__attribute__((used)) static ssize_t ps2_audio_write(void *data, const void *buf, size_t size)
{
   int bytes_sent;
   ps2_audio_t* ps2 = (ps2_audio_t*)data;

   if (!ps2->running)
      return -1;

   bytes_sent = audsrv_play_audio(buf, size);

   return bytes_sent;
}