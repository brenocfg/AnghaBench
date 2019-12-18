#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  t ;
typedef  int /*<<< orphan*/  UCHAR ;
struct TYPE_9__ {int /*<<< orphan*/  StormList; } ;
struct TYPE_8__ {int StrictMode; int /*<<< orphan*/ * MacAddress; int /*<<< orphan*/  DestIp; int /*<<< orphan*/  SrcIp; } ;
typedef  TYPE_1__ STORM ;
typedef  int /*<<< orphan*/  IP ;
typedef  TYPE_2__ HUB_PA ;

/* Variables and functions */
 int /*<<< orphan*/  Copy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 TYPE_1__* Search (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  Zero (TYPE_1__*,int) ; 

STORM *SearchStormList(HUB_PA *pa, UCHAR *mac_address, IP *src_ip, IP *dest_ip, bool strict)
{
	STORM t, *s;
	// Validate arguments
	if (pa == NULL || mac_address == NULL)
	{
		return NULL;
	}

	Zero(&t, sizeof(t));
	if (src_ip != NULL)
	{
		Copy(&t.SrcIp, src_ip, sizeof(IP));
	}
	if (dest_ip != NULL)
	{
		Copy(&t.DestIp, dest_ip, sizeof(IP));
	}
	Copy(t.MacAddress, mac_address, 6);

	t.StrictMode = strict;

	s = Search(pa->StormList, &t);

	return s;
}