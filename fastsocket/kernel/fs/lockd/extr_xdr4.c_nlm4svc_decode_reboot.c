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
struct svc_rqst {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  data; } ;
struct nlm_reboot {TYPE_1__ priv; int /*<<< orphan*/  state; int /*<<< orphan*/  len; int /*<<< orphan*/  mon; } ;
typedef  int /*<<< orphan*/  __be32 ;

/* Variables and functions */
 int /*<<< orphan*/  SM_MAXSTRLEN ; 
 int /*<<< orphan*/  SM_PRIV_SIZE ; 
 int /*<<< orphan*/  XDR_QUADLEN (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  ntohl (int /*<<< orphan*/ ) ; 
 int xdr_argsize_check (struct svc_rqst*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * xdr_decode_string_inplace (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

int
nlm4svc_decode_reboot(struct svc_rqst *rqstp, __be32 *p, struct nlm_reboot *argp)
{
	if (!(p = xdr_decode_string_inplace(p, &argp->mon, &argp->len, SM_MAXSTRLEN)))
		return 0;
	argp->state = ntohl(*p++);
	memcpy(&argp->priv.data, p, sizeof(argp->priv.data));
	p += XDR_QUADLEN(SM_PRIV_SIZE);
	return xdr_argsize_check(rqstp, p);
}