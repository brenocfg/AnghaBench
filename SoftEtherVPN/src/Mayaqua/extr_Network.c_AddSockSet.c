#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {scalar_t__ Type; int Connected; } ;
struct TYPE_5__ {scalar_t__ NumSocket; TYPE_2__** Sock; } ;
typedef  TYPE_1__ SOCKSET ;
typedef  TYPE_2__ SOCK ;

/* Variables and functions */
 scalar_t__ MAX_SOCKSET_NUM ; 
 scalar_t__ SOCK_TCP ; 

void AddSockSet(SOCKSET *set, SOCK *sock)
{
	// Validate arguments
	if (set == NULL || sock == NULL)
	{
		return;
	}
	if (sock->Type == SOCK_TCP && sock->Connected == false)
	{
		return;
	}

	if (set->NumSocket >= MAX_SOCKSET_NUM)
	{
		// Upper limit
		return;
	}
	set->Sock[set->NumSocket++] = sock;
}