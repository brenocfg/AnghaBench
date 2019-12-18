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
struct tcpcb {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  num_sockets; } ;
typedef  int /*<<< orphan*/  SInt32 ;

/* Variables and functions */
 int /*<<< orphan*/  OSDecrementAtomic (int /*<<< orphan*/  volatile*) ; 
 TYPE_1__ tcp_cc_cubic ; 

__attribute__((used)) static int tcp_cubic_cleanup(struct tcpcb *tp)
{
#pragma unused(tp)
	OSDecrementAtomic((volatile SInt32 *)&tcp_cc_cubic.num_sockets);
	return (0);
}