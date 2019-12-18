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
struct in_addr {void* s_addr; } ;
typedef  scalar_t__ s32 ;

/* Variables and functions */
 int TRUE ; 
 scalar_t__ if_configex (struct in_addr*,struct in_addr*,struct in_addr*,int,int) ; 
 void* inet_addr (char*) ; 
 int /*<<< orphan*/  inet_ntoa (struct in_addr) ; 
 int /*<<< orphan*/  strcpy (char*,int /*<<< orphan*/ ) ; 

s32 if_config(char *local_ip, char *netmask, char *gateway,bool use_dhcp, int max_retries)
{
	s32 ret = 0;
	struct in_addr loc_ip, mask, gw;

	loc_ip.s_addr = 0;
	mask.s_addr = 0;
	gw.s_addr = 0;

	if ( local_ip != NULL ) loc_ip.s_addr = inet_addr(local_ip);
	if ( netmask != NULL ) mask.s_addr = inet_addr(netmask);
	if ( gateway != NULL ) gw.s_addr = inet_addr(gateway);

	ret = if_configex( &loc_ip, &mask, &gw, use_dhcp, max_retries);

	if (ret<0) return ret;

	if ( use_dhcp == TRUE ) {
		//copy back network addresses
		if ( local_ip != NULL ) strcpy(local_ip, inet_ntoa( loc_ip ));
		if ( netmask != NULL ) strcpy(netmask, inet_ntoa( mask));
		if ( gateway != NULL ) strcpy(gateway, inet_ntoa( gw ));
	}
	return ret;
}