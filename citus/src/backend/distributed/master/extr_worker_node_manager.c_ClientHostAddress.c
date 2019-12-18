#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {int ss_family; } ;
struct TYPE_9__ {int /*<<< orphan*/  salen; TYPE_4__ addr; } ;
struct TYPE_11__ {TYPE_1__ raddr; } ;
struct TYPE_10__ {char* data; } ;
typedef  TYPE_2__* StringInfo ;
typedef  TYPE_3__ Port ;

/* Variables and functions */
#define  AF_INET 129 
#define  AF_INET6 128 
 TYPE_3__* MyProcPort ; 
 int NI_MAXHOST ; 
 int NI_NAMEREQD ; 
 int /*<<< orphan*/  appendStringInfo (TYPE_2__*,char*,char*) ; 
 char* gai_strerror (int) ; 
 TYPE_2__* makeStringInfo () ; 
 char* palloc0 (int) ; 
 int pg_getnameinfo_all (TYPE_4__*,int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static char *
ClientHostAddress(StringInfo clientHostStringInfo)
{
	Port *port = MyProcPort;
	char *clientHost = NULL;
	char *errorMessage = NULL;
	int clientHostLength = NI_MAXHOST;
	int flags = NI_NAMEREQD;    /* require fully qualified hostname */
	int nameFound = 0;

	if (port == NULL)
	{
		errorMessage = "cannot find tcp/ip connection to client";
		return errorMessage;
	}

	switch (port->raddr.addr.ss_family)
	{
		case AF_INET:
#ifdef HAVE_IPV6
		case AF_INET6:
#endif
			{
				break;
			}

		default:
		{
			errorMessage = "invalid address family in connection";
			return errorMessage;
		}
	}

	clientHost = palloc0(clientHostLength);

	nameFound = pg_getnameinfo_all(&port->raddr.addr, port->raddr.salen,
								   clientHost, clientHostLength, NULL, 0, flags);
	if (nameFound == 0)
	{
		appendStringInfo(clientHostStringInfo, "%s", clientHost);
	}
	else
	{
		StringInfo errorMessageStringInfo = makeStringInfo();
		appendStringInfo(errorMessageStringInfo, "could not resolve client host: %s",
						 gai_strerror(nameFound));

		errorMessage = errorMessageStringInfo->data;
		return errorMessage;
	}

	return errorMessage;
}