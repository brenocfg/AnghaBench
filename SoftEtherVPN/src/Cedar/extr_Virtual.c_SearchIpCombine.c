#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  IpCombine; } ;
typedef  TYPE_1__ VH ;
typedef  int /*<<< orphan*/  USHORT ;
typedef  void* UINT ;
typedef  int /*<<< orphan*/  UCHAR ;
struct TYPE_8__ {int /*<<< orphan*/  Protocol; int /*<<< orphan*/  Id; void* SrcIP; void* DestIP; } ;
typedef  TYPE_2__ IP_COMBINE ;

/* Variables and functions */
 TYPE_2__* Search (int /*<<< orphan*/ ,TYPE_2__*) ; 

IP_COMBINE *SearchIpCombine(VH *v, UINT src_ip, UINT dest_ip, USHORT id, UCHAR protocol)
{
	IP_COMBINE *c, t;
	// Validate arguments
	if (v == NULL)
	{
		return NULL;
	}

	t.DestIP = dest_ip;
	t.SrcIP = src_ip;
	t.Id = id;
	t.Protocol = protocol;

	c = Search(v->IpCombine, &t);

	return c;
}