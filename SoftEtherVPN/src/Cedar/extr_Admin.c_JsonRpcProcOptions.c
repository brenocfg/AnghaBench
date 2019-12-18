#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int JsonRpcAuthed; int /*<<< orphan*/  Listener; } ;
typedef  int /*<<< orphan*/  SOCK ;
typedef  int /*<<< orphan*/  HTTP_HEADER ;
typedef  TYPE_1__ CONNECTION ;

/* Variables and functions */
 int /*<<< orphan*/  AdminWebSendBody (int /*<<< orphan*/ *,int,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  RemoveDosEntry (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void JsonRpcProcOptions(CONNECTION *c, SOCK *s, HTTP_HEADER *h, char *url_target)
{
	if (c == NULL || s == NULL || h == NULL || url_target == NULL)
	{
		return;
	}

	c->JsonRpcAuthed = true;

#ifndef	GC_SOFTETHER_OSS
	RemoveDosEntry(c->Listener, s);
#endif	// GC_SOFTETHER_OSS

	AdminWebSendBody(s, 200, "OK", NULL, 0, NULL, NULL, NULL, h);
}