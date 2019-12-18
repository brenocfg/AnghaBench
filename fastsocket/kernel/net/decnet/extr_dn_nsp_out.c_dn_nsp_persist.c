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
struct sock {int dummy; } ;
struct dn_scp {int nsp_srtt; int nsp_rttvar; size_t nsp_rxtshift; } ;

/* Variables and functions */
 struct dn_scp* DN_SK (struct sock*) ; 
 unsigned long HZ ; 
 size_t NSP_MAXRXTSHIFT ; 
 unsigned long* nsp_backoff ; 

unsigned long dn_nsp_persist(struct sock *sk)
{
	struct dn_scp *scp = DN_SK(sk);

	unsigned long t = ((scp->nsp_srtt >> 2) + scp->nsp_rttvar) >> 1;

	t *= nsp_backoff[scp->nsp_rxtshift];

	if (t < HZ) t = HZ;
	if (t > (600*HZ)) t = (600*HZ);

	if (scp->nsp_rxtshift < NSP_MAXRXTSHIFT)
		scp->nsp_rxtshift++;

	/* printk(KERN_DEBUG "rxtshift %lu, t=%lu\n", scp->nsp_rxtshift, t); */

	return t;
}