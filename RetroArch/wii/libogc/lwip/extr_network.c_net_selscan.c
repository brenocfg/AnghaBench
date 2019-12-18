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
struct netsocket {scalar_t__ sendevt; scalar_t__ rcvevt; scalar_t__ lastdata; } ;
typedef  scalar_t__ s32 ;
typedef  int /*<<< orphan*/  fd_set ;

/* Variables and functions */
 scalar_t__ FD_ISSET (scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FD_SET (scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FD_ZERO (int /*<<< orphan*/ *) ; 
 struct netsocket* get_socket (scalar_t__) ; 

__attribute__((used)) static s32 net_selscan(s32 maxfdp1,fd_set *readset,fd_set *writeset,fd_set *exceptset)
{
	s32 i,nready = 0;
	fd_set lreadset,lwriteset,lexceptset;
	struct netsocket *sock;

	FD_ZERO(&lreadset);
	FD_ZERO(&lwriteset);
	FD_ZERO(&lexceptset);

	for(i=0;i<maxfdp1;i++) {
		if(FD_ISSET(i,readset)) {
			sock = get_socket(i);
			if(sock && (sock->lastdata || sock->rcvevt)) {
				FD_SET(i,&lreadset);
				nready++;
			}
		}
		if(FD_ISSET(i,writeset)) {
			sock = get_socket(i);
			if(sock && sock->sendevt) {
				FD_SET(i,&lwriteset);
				nready++;
			}
		}
	}
	*readset = lreadset;
	*writeset = lwriteset;
	FD_ZERO(exceptset);

	return nready;
}