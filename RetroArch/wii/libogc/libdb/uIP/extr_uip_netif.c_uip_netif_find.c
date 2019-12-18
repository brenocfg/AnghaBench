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
typedef  char u8_t ;
struct uip_netif {char num; char const* name; struct uip_netif* next; } ;

/* Variables and functions */
 struct uip_netif* uip_netif_list ; 

struct uip_netif* uip_netif_find(const char *name)
{
	u8_t num;
	struct uip_netif *netif;

	if(name==NULL) return NULL;

	num = name[2] - '0';

	for(netif=uip_netif_list;netif!=NULL;netif=netif->next) {
		if(netif->num==num &&
			netif->name[0]==name[0] &&
			netif->name[1]==name[1]) return netif;
	}

	return NULL;
}