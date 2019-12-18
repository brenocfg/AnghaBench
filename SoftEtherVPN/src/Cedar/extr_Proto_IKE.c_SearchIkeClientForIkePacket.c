#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_5__ ;
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ UINT ;
struct TYPE_16__ {TYPE_1__* CurrentIkeSa; scalar_t__ ServerPort; int /*<<< orphan*/  ServerIP; scalar_t__ ClientPort; int /*<<< orphan*/  ClientIP; } ;
struct TYPE_15__ {scalar_t__ InitiatorCookie; scalar_t__ ResponderCookie; } ;
struct TYPE_14__ {scalar_t__ InitiatorCookie; scalar_t__ ResponderCookie; TYPE_5__* IkeClient; } ;
struct TYPE_13__ {int /*<<< orphan*/  IkeSaList; int /*<<< orphan*/  ClientList; } ;
struct TYPE_12__ {scalar_t__ InitiatorCookie; scalar_t__ ResponderCookie; } ;
typedef  int /*<<< orphan*/  IP ;
typedef  TYPE_2__ IKE_SERVER ;
typedef  TYPE_3__ IKE_SA ;
typedef  TYPE_4__ IKE_PACKET ;
typedef  TYPE_5__ IKE_CLIENT ;

/* Variables and functions */
 scalar_t__ CmpIpAddr (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Copy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 scalar_t__ IPSEC_PORT_IPSEC_ESP_UDP ; 
 TYPE_3__* LIST_DATA (int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ LIST_NUM (int /*<<< orphan*/ ) ; 
 TYPE_5__* Search (int /*<<< orphan*/ ,TYPE_5__*) ; 

IKE_CLIENT *SearchIkeClientForIkePacket(IKE_SERVER *ike, IP *client_ip, UINT client_port, IP *server_ip, UINT server_port, IKE_PACKET *pr)
{
	IKE_CLIENT t;
	IKE_CLIENT *c = NULL;
	// Validate arguments
	if (ike == NULL || pr == NULL || client_ip == NULL || server_ip == NULL || client_port == 0 || server_port == 0)
	{
		return NULL;
	}

	if (true)
	{
		UINT i;

		if (pr->InitiatorCookie != 0 && pr->ResponderCookie != 0)
		{
			for (i = 0;i < LIST_NUM(ike->IkeSaList);i++)
			{
				IKE_SA *sa = LIST_DATA(ike->IkeSaList, i);

				// Extract what Cookie matches exactly
				if (sa->InitiatorCookie == pr->InitiatorCookie && sa->ResponderCookie == pr->ResponderCookie)
				{
					IKE_CLIENT *cc = sa->IkeClient;

					if (CmpIpAddr(&cc->ServerIP, server_ip) == 0 &&
						CmpIpAddr(&cc->ClientIP, client_ip) == 0)
					{
						c = cc;
						break;
					}
				}
			}
		}
	}

	if (c == NULL)
	{
		// Search by a pair of IP address and port number
		Copy(&t.ClientIP, client_ip, sizeof(IP));
		t.ClientPort = client_port;
		Copy(&t.ServerIP, server_ip, sizeof(IP));
		t.ServerPort = server_port;

		c = Search(ike->ClientList, &t);

		if (c != NULL)// && server_port == IPSEC_PORT_IPSEC_ISAKMP)
		{
			// Search that the IKE_SA that points to this IKE_CLIENT exists and match the Cookie
			bool ok = false;
			UINT i;

			if (server_port == IPSEC_PORT_IPSEC_ESP_UDP)
			{
				// Regard as OK if the port number exactly match in the case of connecting to a server-side 4500
				ok = true;
			}
			else
			{
				if (c->CurrentIkeSa != NULL &&
					c->CurrentIkeSa->InitiatorCookie == pr->InitiatorCookie &&
					c->CurrentIkeSa->ResponderCookie == pr->ResponderCookie)
				{
					ok = true;
				}
				else 
				{
					for (i = 0;i < LIST_NUM(ike->IkeSaList);i++)
					{
						IKE_SA *sa = LIST_DATA(ike->IkeSaList, i);

						if (sa->IkeClient == c)
						{
							if (sa->InitiatorCookie == pr->InitiatorCookie &&
								sa->ResponderCookie == pr->ResponderCookie)
							{
								ok = true;
								break;
							}
						}
					}
				}
			}

			if (ok == false)
			{
				// Not found
				c = NULL;
			}
		}
	}

	return c;
}