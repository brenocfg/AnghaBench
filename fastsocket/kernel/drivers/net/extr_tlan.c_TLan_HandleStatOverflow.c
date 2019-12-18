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
typedef  int u32 ;
typedef  int /*<<< orphan*/  u16 ;
struct net_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  TLAN_RECORD ; 
 int /*<<< orphan*/  TLan_ReadAndClearStats (struct net_device*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static u32 TLan_HandleStatOverflow( struct net_device *dev, u16 host_int )
{
	TLan_ReadAndClearStats( dev, TLAN_RECORD );

	return 1;

}