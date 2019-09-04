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
struct TYPE_3__ {scalar_t__ WaitToUseCipher; } ;
typedef  TYPE_1__ SOCK ;

/* Variables and functions */
 scalar_t__ CopyStr (char*) ; 
 int /*<<< orphan*/  Free (scalar_t__) ; 

void SetWantToUseCipher(SOCK *sock, char *name)
{
	// Validate arguments
	if (sock == NULL || name == NULL)
	{
		return;
	}

	if (sock->WaitToUseCipher)
	{
		Free(sock->WaitToUseCipher);
	}

	sock->WaitToUseCipher = CopyStr(name);
}