#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_4__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  carttype; } ;
struct TYPE_5__ {int RBR; int IER; int DLL; int DLM; int IIR; int LCR; int MCR; int LSR; int MSR; int SCR; int* SREG; } ;
struct TYPE_6__ {int isechoenab; int thb_write_time; int connect_timeout; int /*<<< orphan*/  portstring; int /*<<< orphan*/  ipstring; TYPE_1__ reg; scalar_t__ escape_count; int /*<<< orphan*/  modemstate; scalar_t__ cycles; scalar_t__ outbufferupdate; scalar_t__ outbuffersize; scalar_t__ outbufferend; scalar_t__ outbufferstart; scalar_t__ inbufferupdate; scalar_t__ inbuffersize; scalar_t__ inbufferend; scalar_t__ inbufferstart; scalar_t__ outbuffer; scalar_t__ inbuffer; } ;
typedef  int /*<<< orphan*/  Netlink ;

/* Variables and functions */
 int /*<<< orphan*/  CART_NONE ; 
 TYPE_4__* Cs2Area ; 
 int /*<<< orphan*/  NETLINK_BUFFER_SIZE ; 
 int /*<<< orphan*/  NL_MODEMSTATE_COMMAND ; 
 TYPE_2__* NetlinkArea ; 
 int NetworkInit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  YAB_ERR_CANNOTINIT ; 
 int /*<<< orphan*/  YabSetError (int /*<<< orphan*/ ,void*) ; 
 TYPE_2__* malloc (int) ; 
 int /*<<< orphan*/  memset (void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sprintf (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ strcmp (char const*,char*) ; 
 int /*<<< orphan*/  strcpy (int /*<<< orphan*/ ,char const*) ; 

int NetlinkInit(const char *ip, const char *port)
{  
   if ((NetlinkArea = malloc(sizeof(Netlink))) == NULL)
   {
      Cs2Area->carttype = CART_NONE;
      YabSetError(YAB_ERR_CANNOTINIT, (void *)"Netlink");
      return 0;
   }

   memset((void *) NetlinkArea->inbuffer, 0, NETLINK_BUFFER_SIZE);
   memset((void *) NetlinkArea->outbuffer, 0, NETLINK_BUFFER_SIZE);

   NetlinkArea->inbufferstart = NetlinkArea->inbufferend = NetlinkArea->inbuffersize = 0;
   NetlinkArea->inbufferupdate = 0;
   NetlinkArea->outbufferstart = NetlinkArea->outbufferend = NetlinkArea->outbuffersize = 0;
   NetlinkArea->outbufferupdate = 0;

   NetlinkArea->isechoenab = 1;
   NetlinkArea->cycles = 0;
   NetlinkArea->thb_write_time = 0xFFFFFFFF;
   NetlinkArea->modemstate = NL_MODEMSTATE_COMMAND;
   NetlinkArea->escape_count = 0;

   NetlinkArea->reg.RBR = 0x00;
   NetlinkArea->reg.IER = 0x00;
   NetlinkArea->reg.DLL = 0x00;
   NetlinkArea->reg.DLM = 0x00;
   NetlinkArea->reg.IIR = 0x01;
//      NetlinkArea->reg.FCR = 0x??; // have no idea
   NetlinkArea->reg.LCR = 0x00;
   NetlinkArea->reg.MCR = 0x00;
   NetlinkArea->reg.LSR = 0x60;
   NetlinkArea->reg.MSR = 0x30;
   NetlinkArea->reg.SCR = 0x01;

   NetlinkArea->reg.SREG[7] = 50;
   NetlinkArea->connect_timeout = NetlinkArea->reg.SREG[7] * 1000000;

   if (ip == NULL || strcmp(ip, "") == 0)
      // Use Loopback ip
      sprintf(NetlinkArea->ipstring, "127.0.0.1");
	else
		strcpy(NetlinkArea->ipstring, ip);

	if (port == NULL || strcmp(port, "") == 0)
		// Default port
      sprintf(NetlinkArea->portstring, "1337");
	else
		strcpy(NetlinkArea->portstring, port);

#ifdef USESOCKET
   return NetworkInit(NetlinkArea->portstring);
#else
   return 0;
#endif
}