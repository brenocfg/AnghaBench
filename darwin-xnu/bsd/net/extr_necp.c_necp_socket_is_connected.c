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
struct inpcb {TYPE_1__* inp_socket; } ;
struct TYPE_2__ {int so_state; } ;

/* Variables and functions */
 int SS_ISCONNECTED ; 
 int SS_ISCONNECTING ; 
 int SS_ISDISCONNECTING ; 

__attribute__((used)) static inline bool
necp_socket_is_connected(struct inpcb *inp)
{
	return (inp->inp_socket->so_state & (SS_ISCONNECTING | SS_ISCONNECTED | SS_ISDISCONNECTING));
}