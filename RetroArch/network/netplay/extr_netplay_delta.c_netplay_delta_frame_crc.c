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
typedef  int /*<<< orphan*/  uint32_t ;
struct delta_frame {scalar_t__ state; } ;
struct TYPE_3__ {int /*<<< orphan*/  state_size; } ;
typedef  TYPE_1__ netplay_t ;

/* Variables and functions */
 int /*<<< orphan*/  encoding_crc32 (long,unsigned char const*,int /*<<< orphan*/ ) ; 

uint32_t netplay_delta_frame_crc(netplay_t *netplay, struct delta_frame *delta)
{
   if (!netplay->state_size)
      return 0;
   return encoding_crc32(0L, (const unsigned char*)delta->state, netplay->state_size);
}