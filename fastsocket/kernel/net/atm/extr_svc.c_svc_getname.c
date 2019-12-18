#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct socket {int dummy; } ;
struct sockaddr_atmsvc {int dummy; } ;
struct sockaddr {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  local; int /*<<< orphan*/  remote; } ;

/* Variables and functions */
 TYPE_1__* ATM_SD (struct socket*) ; 
 int /*<<< orphan*/  memcpy (struct sockaddr_atmsvc*,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int svc_getname(struct socket *sock,struct sockaddr *sockaddr,
    int *sockaddr_len,int peer)
{
	struct sockaddr_atmsvc *addr;

	*sockaddr_len = sizeof(struct sockaddr_atmsvc);
	addr = (struct sockaddr_atmsvc *) sockaddr;
	memcpy(addr,peer ? &ATM_SD(sock)->remote : &ATM_SD(sock)->local,
	    sizeof(struct sockaddr_atmsvc));
	return 0;
}