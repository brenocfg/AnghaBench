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
 int rpcb_create_local () ; 
 int /*<<< orphan*/  svc_unregister (struct svc_serv*) ; 

__attribute__((used)) static int svc_rpcb_setup(struct svc_serv *serv)
{
	int err;

	err = rpcb_create_local();
	if (err)
		return err;

	/* Remove any stale portmap registrations */
	svc_unregister(serv);
	return 0;
}