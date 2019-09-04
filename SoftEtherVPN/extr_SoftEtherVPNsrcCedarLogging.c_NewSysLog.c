#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  UINT ;
struct TYPE_5__ {int /*<<< orphan*/  Udp; int /*<<< orphan*/  lock; } ;
typedef  TYPE_1__ SLOG ;
typedef  int /*<<< orphan*/  IP ;

/* Variables and functions */
 int /*<<< orphan*/  NewLock () ; 
 int /*<<< orphan*/  NewUDPEx2 (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SetSysLog (TYPE_1__*,char*,int /*<<< orphan*/ ) ; 
 TYPE_1__* ZeroMalloc (int) ; 

SLOG *NewSysLog(char *hostname, UINT port, IP *ip)
{
	// Validate arguments
	SLOG *g = ZeroMalloc(sizeof(SLOG));

	g->lock = NewLock();
	g->Udp = NewUDPEx2(0, false, ip);

	SetSysLog(g, hostname, port);

	return g;
}