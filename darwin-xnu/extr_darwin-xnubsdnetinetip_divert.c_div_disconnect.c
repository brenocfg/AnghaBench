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
struct socket {int so_state; } ;

/* Variables and functions */
 int ENOTCONN ; 
 int SS_ISCONNECTED ; 
 int div_abort (struct socket*) ; 

__attribute__((used)) static int
div_disconnect(struct socket *so)
{
	if ((so->so_state & SS_ISCONNECTED) == 0)
		return ENOTCONN;
	return div_abort(so);
}