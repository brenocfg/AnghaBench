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
struct svc_serv {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  rpcb_put_local () ; 
 int /*<<< orphan*/  svc_unregister (struct svc_serv*) ; 

void svc_rpcb_cleanup(struct svc_serv *serv)
{
	svc_unregister(serv);
	rpcb_put_local();
}