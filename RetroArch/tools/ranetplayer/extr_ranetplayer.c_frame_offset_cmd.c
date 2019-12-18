#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;

/* Variables and functions */
#define  NETPLAY_CMD_CRC 133 
#define  NETPLAY_CMD_INPUT 132 
#define  NETPLAY_CMD_LOAD_SAVESTATE 131 
#define  NETPLAY_CMD_MODE 130 
#define  NETPLAY_CMD_NOINPUT 129 
#define  NETPLAY_CMD_RESET 128 
 int cmd ; 
 int /*<<< orphan*/  frame_offset ; 
 int /*<<< orphan*/  htonl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ntohl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * payload ; 

uint32_t frame_offset_cmd(bool ntoh)
{
   uint32_t frame = 0;

   switch (cmd)
   {
      case NETPLAY_CMD_INPUT:
      case NETPLAY_CMD_NOINPUT:
      case NETPLAY_CMD_MODE:
      case NETPLAY_CMD_CRC:
      case NETPLAY_CMD_LOAD_SAVESTATE:
      case NETPLAY_CMD_RESET:
         frame = ntohl(payload[0]);
         if (ntoh)
            frame -= frame_offset;
         else
            frame += frame_offset;
         payload[0] = htonl(frame);
         break;
   }

   return frame;
}