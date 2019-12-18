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
struct PortMappingParserData {int curelt; struct PortMapping* l_head; } ;
struct PortMapping {char* remoteHost; unsigned short externalPort; char* protocol; unsigned short internalPort; char* internalClient; unsigned char enabled; char* description; scalar_t__ leaseTime; } ;

/* Variables and functions */
#define  NewDescription 135 
#define  NewEnabled 134 
#define  NewExternalPort 133 
#define  NewInternalClient 132 
#define  NewInternalPort 131 
#define  NewLeaseTime 130 
#define  NewProtocol 129 
#define  NewRemoteHost 128 
 int /*<<< orphan*/  memcpy (char*,char const*,int) ; 
 scalar_t__ my_atoui (char const*,int) ; 

__attribute__((used)) static void portlisting_data(void * d, const char * data, int l)
{
	struct PortMapping * pm;
	struct PortMappingParserData * pdata = (struct PortMappingParserData *)d;
	pm = pdata->l_head;
	if(!pm)
		return;
	if(l > 63)
		l = 63;
	switch(pdata->curelt)
	{
	case NewRemoteHost:
		memcpy(pm->remoteHost, data, l);
		pm->remoteHost[l] = '\0';
		break;
	case NewExternalPort:
		pm->externalPort = (unsigned short)my_atoui(data, l);
		break;
	case NewProtocol:
		if(l > 3)
			l = 3;
		memcpy(pm->protocol, data, l);
		pm->protocol[l] = '\0';
		break;
	case NewInternalPort:
		pm->internalPort = (unsigned short)my_atoui(data, l);
		break;
	case NewInternalClient:
		memcpy(pm->internalClient, data, l);
		pm->internalClient[l] = '\0';
		break;
	case NewEnabled:
		pm->enabled = (unsigned char)my_atoui(data, l);
		break;
	case NewDescription:
		memcpy(pm->description, data, l);
		pm->description[l] = '\0';
		break;
	case NewLeaseTime:
		pm->leaseTime = my_atoui(data, l);
		break;
	default:
		break;
	}
}