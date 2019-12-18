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
struct netsocket {int /*<<< orphan*/  conn; } ;
typedef  size_t s32 ;

/* Variables and functions */
 int /*<<< orphan*/  LWIP_DEBUGF (int /*<<< orphan*/ ,char*) ; 
 size_t NUM_SOCKETS ; 
 int /*<<< orphan*/  SOCKETS_DEBUG ; 
 struct netsocket* sockets ; 

__attribute__((used)) static struct netsocket* get_socket(s32 s)
{
	struct netsocket *sock;
	if(s<0 || s>NUM_SOCKETS) {
	    LWIP_DEBUGF(SOCKETS_DEBUG, ("get_socket(%d): invalid\n", s));
		return NULL;
	}
	sock = &sockets[s];
	if(!sock->conn) {
	    LWIP_DEBUGF(SOCKETS_DEBUG, ("get_socket(%d): no active\n", s));
		return NULL;
	}

	return sock;
}