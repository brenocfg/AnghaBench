#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  UINT ;
struct TYPE_7__ {int /*<<< orphan*/  ClientList; } ;
typedef  int /*<<< orphan*/  IP ;
typedef  TYPE_1__ IKE_SERVER ;
typedef  int /*<<< orphan*/  IKE_PACKET ;
typedef  int /*<<< orphan*/  IKE_CLIENT ;

/* Variables and functions */
 scalar_t__ GetNumberOfIkeClientsFromIP (TYPE_1__*,int /*<<< orphan*/ *) ; 
 scalar_t__ IKE_QUOTA_MAX_NUM_CLIENTS ; 
 scalar_t__ IKE_QUOTA_MAX_NUM_CLIENTS_PER_IP ; 
 int /*<<< orphan*/  Insert (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ LIST_NUM (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * NewIkeClient (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SearchIkeClientForIkePacket (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * SetIkeClientEndpoint (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

IKE_CLIENT *SearchOrCreateNewIkeClientForIkePacket(IKE_SERVER *ike, IP *client_ip, UINT client_port, IP *server_ip, UINT server_port, IKE_PACKET *pr)
{
	IKE_CLIENT *c;
	// Validate arguments
	if (ike == NULL || pr == NULL || client_ip == NULL || server_ip == NULL || client_port == 0 || server_port == 0)
	{
		return NULL;
	}

	c = SearchIkeClientForIkePacket(ike, client_ip, client_port, server_ip, server_port, pr);
	if (c == NULL)
	{
		if (GetNumberOfIkeClientsFromIP(ike, client_ip) > IKE_QUOTA_MAX_NUM_CLIENTS_PER_IP ||
			LIST_NUM(ike->ClientList) > IKE_QUOTA_MAX_NUM_CLIENTS)
		{
			return NULL;
		}


		c = NewIkeClient(ike, client_ip, client_port, server_ip, server_port);

		Insert(ike->ClientList, c);
	}

	return SetIkeClientEndpoint(ike, c, client_ip, client_port, server_ip, server_port);
}