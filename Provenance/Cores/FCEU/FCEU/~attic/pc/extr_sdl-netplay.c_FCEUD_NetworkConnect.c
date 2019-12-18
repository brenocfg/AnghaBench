#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8 ;
typedef  int uint32 ;
typedef  int /*<<< orphan*/  Uint16 ;
struct TYPE_6__ {void* port; } ;
typedef  void* TCPsocket ;
typedef  TYPE_1__ IPaddress ;

/* Variables and functions */
 int /*<<< orphan*/  LocalPortTCP ; 
 int /*<<< orphan*/  LocalPortUDP ; 
 int /*<<< orphan*/  RemotePortTCP ; 
 void* RemotePortUDP ; 
 int /*<<< orphan*/  SDLNet_AllocSocketSet (int) ; 
 int /*<<< orphan*/  SDLNet_Init () ; 
 int /*<<< orphan*/  SDLNet_ResolveHost (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 void* SDLNet_TCP_Accept (void**) ; 
 int /*<<< orphan*/  SDLNet_TCP_AddSocket (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SDLNet_TCP_GetPeerAddress (void*) ; 
 void* SDLNet_TCP_Open (TYPE_1__*) ; 
 int /*<<< orphan*/  SDLNet_TCP_Recv (void*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  SDLNet_TCP_Send (void*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  SDLNet_UDP_AddSocket (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SDLNet_UDP_Bind (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  SDLNet_UDP_Open (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SDLNet_Write32 (int /*<<< orphan*/ *,int) ; 
 int SDL_GetTicks () ; 
 int /*<<< orphan*/ * ServerHost ; 
 void* Socket ; 
 int /*<<< orphan*/  TCPSocket ; 
 int /*<<< orphan*/  UDPSocket ; 
 void* de32 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  en32 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int magic ; 
 int /*<<< orphan*/  memcpy (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int netplay ; 
 int /*<<< orphan*/  set ; 
 int uport ; 

int FCEUD_NetworkConnect(void)
{
 IPaddress rip;

 SDLNet_Init();

 if(netplay==1)	/* Be a server. */
 {
  TCPsocket tmp;
  Uint16 p=LocalPortUDP;

  SDLNet_ResolveHost(&rip,NULL,LocalPortTCP);

  UDPSocket=SDLNet_UDP_Open(&p);

  tmp=SDLNet_TCP_Open(&rip);
  Socket=SDLNet_TCP_Accept(&tmp);

  memcpy(&rip,SDLNet_TCP_GetPeerAddress(Socket),sizeof(IPaddress));

  {
   uint8 buf[12];
   uint32 player=1;

   magic=SDL_GetTicks();

   SDLNet_Write32(buf,uport);
   SDLNet_Write32(buf+4,1);
   SDLNet_Write32(buf+8,magic);

   SDLNet_TCP_Send(Socket, buf, 12);

   /* Get the UDP port the client is waiting for data on. */
   SDLNet_TCP_Recv(Socket, buf, 2);
   RemotePortUDP=de32(buf);
  }
 }
 else		/* Be a client	*/
 {
  SDLNet_ResolveHost(&rip,ServerHost,RemotePortTCP);
  Socket=SDLNet_TCP_Open(&rip);

  {
   Uint16 p=LocalPortUDP;
   uint8 buf[12];
  
   UDPSocket=SDLNet_UDP_Open(&p);

   /* Now, tell the server what local UDP port it should send to. */
   en32(buf,p);
   SDLNet_TCP_Send(Socket, buf, 4);
 
   /* Get the UDP port from the server we should send data to. */
   SDLNet_TCP_Recv(Socket, buf, 12);
   RemotePortUDP=de32(buf);
   magic=de32(buf+8);
  }
  set=SDLNet_AllocSocketSet(1);
  SDLNet_TCP_AddSocket(set,TCPSocket);
  SDLNet_UDP_AddSocket(set,UDPSocket);
 }	// End client connect code.

 rip.port=RemotePortUDP;
 SDLNet_UDP_Bind(UDPSocket, 0, &rip);
}