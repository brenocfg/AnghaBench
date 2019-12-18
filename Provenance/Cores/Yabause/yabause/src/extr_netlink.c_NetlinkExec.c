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
typedef  scalar_t__ u32 ;
struct TYPE_2__ {int cycles; int thb_write_time; int escape_count; int connectstatus; int /*<<< orphan*/  outbufferupdate; int /*<<< orphan*/  connect_timeout; int /*<<< orphan*/  connect_time; int /*<<< orphan*/  internet_enable; void* modemstate; } ;

/* Variables and functions */
 int /*<<< orphan*/  NETLINK_LOG (char*) ; 
#define  NL_CONNECTSTATUS_CONNECT 130 
#define  NL_CONNECTSTATUS_CONNECTED 129 
#define  NL_CONNECTSTATUS_IDLE 128 
 int NL_CONNECTSTATUS_LOGIN1 ; 
 void* NL_MODEMSTATE_COMMAND ; 
 void* NL_MODEMSTATE_DATA ; 
 TYPE_1__* NetlinkArea ; 
 int /*<<< orphan*/  NetlinkDoATResponse (char*) ; 
 int /*<<< orphan*/  NetlinkMSRChange (int,int) ; 
 int /*<<< orphan*/  NetlinkUpdateReceivedDataInt () ; 
 int /*<<< orphan*/  NetworkStopConnect () ; 
 int /*<<< orphan*/  NetworkWaitForConnect () ; 

void NetlinkExec(u32 timing)
{
   NetlinkArea->cycles += timing;
   NetlinkArea->connect_time += timing;
   if (NetlinkArea->thb_write_time != 0xFFFFFFFF)
      NetlinkArea->thb_write_time += timing;

   if (NetlinkArea->cycles >= 20000)
   {
      NetlinkArea->cycles -= 20000;

      if (NetlinkArea->escape_count == 3 && NetlinkArea->thb_write_time >= 1000000)
      {
         // Switch back to command mode
         NETLINK_LOG("Detected escape sequence, switching back to command mode\n");
         NetlinkArea->modemstate = NL_MODEMSTATE_COMMAND;
      }

      switch(NetlinkArea->connectstatus)
      {
         case NL_CONNECTSTATUS_IDLE:
         {
#ifdef USESOCKET
            if (NetworkWaitForConnect() == 0)
            {
               NetlinkArea->connectstatus = NL_CONNECTSTATUS_CONNECTED;
               NetlinkArea->modemstate = NL_MODEMSTATE_DATA;

               // This is probably wrong, but let's give it a try anyways
               NetlinkDoATResponse("\r\nRING\r\n\r\nCONNECT\r\n");
               NetlinkMSRChange(0x08, 0x00);
               NetlinkUpdateReceivedDataInt();

               NETLINK_LOG("Connected via listener\n");
            }
#endif
            break;
         }
         case NL_CONNECTSTATUS_CONNECT:
         {
#ifdef USESOCKET
            if (NetlinkArea->internet_enable || NetworkWaitForConnect() == 0)
            {
               NetlinkArea->connectstatus = NL_CONNECTSTATUS_CONNECTED;
               NetlinkArea->modemstate = NL_MODEMSTATE_DATA;

               NetlinkDoATResponse("\r\nCONNECT 28800\r\n");
               NetlinkMSRChange(0x08, 0x00);
               NetlinkUpdateReceivedDataInt();
               NETLINK_LOG("Connected via remote ip connect\n");

               if (NetlinkArea->internet_enable)
               {
                  NetlinkArea->connectstatus = NL_CONNECTSTATUS_LOGIN1;
                  NetlinkDoATResponse("\r\nlogin:");
               }
            }
            else if (NetlinkArea->connect_time >= NetlinkArea->connect_timeout)
            {
               // Kill connect attempt
               NetworkStopConnect();
               NetlinkDoATResponse("\r\nNO ANSWER\r\n");
               NetlinkUpdateReceivedDataInt();
               NetlinkArea->connectstatus = NL_CONNECTSTATUS_IDLE;
            }
#endif
            break;
         }
         case NL_CONNECTSTATUS_CONNECTED:
         {
#ifdef USESOCKET

            if (NetlinkArea->outbufferupdate)
            {
               NetlinkMSRChange(0x08, 0x00);
               NetlinkUpdateReceivedDataInt();

               //NETLINK_LOG("Received %d byte(s) from external source\n", NetlinkArea->bytes_read);
               NetlinkArea->outbufferupdate = 0;
            }
#endif

            break;
         }
         default: break;
      }
   }
}