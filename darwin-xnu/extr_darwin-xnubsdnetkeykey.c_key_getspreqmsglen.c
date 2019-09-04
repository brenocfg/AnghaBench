#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int u_int ;
struct secpolicy {scalar_t__ policy; struct ipsecrequest* req; } ;
struct sadb_x_policy {int dummy; } ;
struct sadb_x_ipsecrequest {int dummy; } ;
struct TYPE_4__ {int ss_len; } ;
struct TYPE_5__ {int ss_len; } ;
struct TYPE_6__ {TYPE_1__ dst; TYPE_2__ src; } ;
struct ipsecrequest {TYPE_3__ saidx; struct ipsecrequest* next; } ;

/* Variables and functions */
 scalar_t__ IPSEC_POLICY_IPSEC ; 
 scalar_t__ PFKEY_ALIGN8 (int) ; 

__attribute__((used)) static u_int
key_getspreqmsglen(
				   struct secpolicy *sp)
{
	u_int tlen;
	
	tlen = sizeof(struct sadb_x_policy);
	
	/* if is the policy for ipsec ? */
	if (sp->policy != IPSEC_POLICY_IPSEC)
		return tlen;
	
	/* get length of ipsec requests */
    {
		struct ipsecrequest *isr;
		int len;
		
		for (isr = sp->req; isr != NULL; isr = isr->next) {
			len = sizeof(struct sadb_x_ipsecrequest)
			+ isr->saidx.src.ss_len
			+ isr->saidx.dst.ss_len;
			
			tlen += PFKEY_ALIGN8(len);
		}
    }
	
	return tlen;
}