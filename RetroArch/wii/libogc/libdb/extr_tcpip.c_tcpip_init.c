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
typedef  int /*<<< orphan*/  uipdev_s ;
typedef  int /*<<< orphan*/  u16 ;
struct uip_netif {int dummy; } ;
struct uip_ip_addr {int dummy; } ;
struct tcpip_sock {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  s_addr; } ;
struct sockaddr_in {int /*<<< orphan*/  sin_family; int /*<<< orphan*/  sin_port; TYPE_1__ sin_addr; } ;
struct sockaddr {int dummy; } ;
struct dbginterface {int fhndl; int /*<<< orphan*/  write; int /*<<< orphan*/  read; int /*<<< orphan*/  close; int /*<<< orphan*/  open; int /*<<< orphan*/  wait; } ;
typedef  int socklen_t ;

/* Variables and functions */
 int /*<<< orphan*/  AF_INET ; 
 int /*<<< orphan*/  INADDR_ANY ; 
 int /*<<< orphan*/  UIP_MEMSET (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int UIP_TCPIP_SOCKS ; 
 int /*<<< orphan*/  closetcpip ; 
 int /*<<< orphan*/  htons (int /*<<< orphan*/ ) ; 
 int listensock ; 
 int /*<<< orphan*/  memr_init () ; 
 int /*<<< orphan*/  netif ; 
 struct dbginterface netif_device ; 
 int /*<<< orphan*/  opentcpip ; 
 int /*<<< orphan*/  readtcpip ; 
 scalar_t__ tcpip_bind (int,struct sockaddr*,int*) ; 
 int /*<<< orphan*/  tcpip_close (int) ; 
 scalar_t__ tcpip_listen (int,int) ; 
 int tcpip_socket () ; 
 int /*<<< orphan*/  tcpip_socks ; 
 int /*<<< orphan*/  uip_bba_create (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  uip_bba_init ; 
 int /*<<< orphan*/  uip_ipinit () ; 
 int /*<<< orphan*/  uip_ipinput ; 
 struct uip_netif* uip_netif_add (int /*<<< orphan*/ *,struct uip_ip_addr*,struct uip_ip_addr*,struct uip_ip_addr*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uip_netif_init () ; 
 int /*<<< orphan*/  uip_netif_setdefault (struct uip_netif*) ; 
 int /*<<< orphan*/  uip_pbuf_init () ; 
 int /*<<< orphan*/  uip_tcp_init () ; 
 int /*<<< orphan*/  waittcpip ; 
 int /*<<< orphan*/  writetcpip ; 

struct dbginterface* tcpip_init(struct uip_ip_addr *localip,struct uip_ip_addr *netmask,struct uip_ip_addr *gateway,u16 port)
{
	uipdev_s hbba;
	struct uip_netif *pnet ;
	struct sockaddr_in name;
	socklen_t namelen = sizeof(struct sockaddr);

	memr_init();
	uip_ipinit();
	uip_pbuf_init();
	uip_netif_init();
	uip_tcp_init();

	UIP_MEMSET(tcpip_socks,0,(UIP_TCPIP_SOCKS*sizeof(struct tcpip_sock)));

	hbba = uip_bba_create(&netif);
	pnet = uip_netif_add(&netif,localip,netmask,gateway,hbba,uip_bba_init,uip_ipinput);
	if(pnet) {
		uip_netif_setdefault(pnet);

		listensock = tcpip_socket();
		if(listensock<0) return NULL;

		name.sin_addr.s_addr = INADDR_ANY;
		name.sin_port = htons(port);
		name.sin_family = AF_INET;

		if(tcpip_bind(listensock,(struct sockaddr*)&name,&namelen)<0){
			tcpip_close(listensock);
			listensock = -1;
			return NULL;
		}
		if(tcpip_listen(listensock,1)<0) {
			tcpip_close(listensock);
			listensock = -1;
			return NULL;
		}

		netif_device.fhndl = -1;
		netif_device.wait = waittcpip;
		netif_device.open = opentcpip;
		netif_device.close = closetcpip;
		netif_device.read = readtcpip;
		netif_device.write = writetcpip;

		return &netif_device;
	}
	return NULL;
}