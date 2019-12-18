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
struct net_device {int /*<<< orphan*/  base_addr; } ;

/* Variables and functions */
 scalar_t__ TLAN_AREG_0 ; 
 int /*<<< orphan*/  TLan_DioWrite8 (int /*<<< orphan*/ ,scalar_t__,char) ; 

__attribute__((used)) static void TLan_SetMac( struct net_device *dev, int areg, char *mac )
{
	int i;

	areg *= 6;

	if ( mac != NULL ) {
		for ( i = 0; i < 6; i++ )
			TLan_DioWrite8( dev->base_addr,
					TLAN_AREG_0 + areg + i, mac[i] );
	} else {
		for ( i = 0; i < 6; i++ )
			TLan_DioWrite8( dev->base_addr,
					TLAN_AREG_0 + areg + i, 0 );
	}

}