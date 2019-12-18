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
struct TYPE_4__ {void* disconnect_lock; void* ssl_lock; int /*<<< orphan*/  socket; int /*<<< orphan*/  SendBuf; void* lock; int /*<<< orphan*/  ref; } ;
typedef  TYPE_1__ SOCK ;

/* Variables and functions */
 int /*<<< orphan*/  INVALID_SOCKET ; 
 int /*<<< orphan*/  Inc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NewBuf () ; 
 void* NewLock () ; 
 int /*<<< orphan*/  NewRef () ; 
 TYPE_1__* ZeroMallocFast (int) ; 
 int /*<<< orphan*/  num_tcp_connections ; 

SOCK *NewSock()
{
	SOCK *s = ZeroMallocFast(sizeof(SOCK));

	s->ref = NewRef();
	s->lock = NewLock();
	s->SendBuf = NewBuf();
	s->socket = INVALID_SOCKET;
	s->ssl_lock = NewLock();
	s->disconnect_lock = NewLock();

	Inc(num_tcp_connections);

	return s;
}