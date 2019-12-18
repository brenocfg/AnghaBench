#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  qboolean ;
struct TYPE_4__ {scalar_t__ type; scalar_t__* ip; scalar_t__ port; int /*<<< orphan*/  ipx; } ;
typedef  TYPE_1__ netadr_t ;

/* Variables and functions */
 int /*<<< orphan*/  Com_Printf (char*) ; 
 scalar_t__ NA_IP ; 
 scalar_t__ NA_IPX ; 
 scalar_t__ NA_LOOPBACK ; 
 scalar_t__ memcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  qfalse ; 
 int /*<<< orphan*/  qtrue ; 

qboolean	NET_CompareAdr (netadr_t a, netadr_t b)
{
	if (a.type != b.type)
		return qfalse;

	if (a.type == NA_LOOPBACK)
		return qtrue;

	if (a.type == NA_IP)
	{
		if (a.ip[0] == b.ip[0] && a.ip[1] == b.ip[1] && a.ip[2] == b.ip[2] && a.ip[3] == b.ip[3] && a.port == b.port)
			return qtrue;
		return qfalse;
	}

	if (a.type == NA_IPX)
	{
		if ((memcmp(a.ipx, b.ipx, 10) == 0) && a.port == b.port)
			return qtrue;
		return qfalse;
	}

	Com_Printf ("NET_CompareAdr: bad address type\n");
	return qfalse;
}