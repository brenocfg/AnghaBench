#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct sockaddr {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  ss_len; } ;
struct secasindex {scalar_t__ ipsec_ifindex; scalar_t__ proto; scalar_t__ mode; scalar_t__ reqid; TYPE_1__ dst; TYPE_1__ src; } ;

/* Variables and functions */
 int CMP_EXACTLY ; 
 int CMP_MODE ; 
 int CMP_PORT ; 
 int CMP_REQID ; 
 scalar_t__ IPSEC_MODE_ANY ; 
 scalar_t__ bcmp (TYPE_1__*,TYPE_1__*,int /*<<< orphan*/ ) ; 
 scalar_t__ key_sockaddrcmp (struct sockaddr*,struct sockaddr*,int) ; 

__attribute__((used)) static int
key_cmpsaidx(
			 struct secasindex *saidx0,
			 struct secasindex *saidx1,
			 int flag)
{
	/* sanity */
	if (saidx0 == NULL && saidx1 == NULL)
		return 1;
	
	if (saidx0 == NULL || saidx1 == NULL)
		return 0;
	
	if (saidx0->ipsec_ifindex != 0 && saidx0->ipsec_ifindex != saidx1->ipsec_ifindex)
		return 0;
	
	if (saidx0->proto != saidx1->proto)
		return 0;
	
	if (flag == CMP_EXACTLY) {
		if (saidx0->mode != saidx1->mode)
			return 0;
		if (saidx0->reqid != saidx1->reqid)
			return 0;
		if (bcmp(&saidx0->src, &saidx1->src, saidx0->src.ss_len) != 0 ||
		    bcmp(&saidx0->dst, &saidx1->dst, saidx0->dst.ss_len) != 0)
			return 0;
	} else {
		
		/* CMP_MODE_REQID, CMP_REQID, CMP_HEAD */
		if (flag & CMP_REQID) {
			/*
			 * If reqid of SPD is non-zero, unique SA is required.
			 * The result must be of same reqid in this case.
			 */
			if (saidx1->reqid != 0 && saidx0->reqid != saidx1->reqid)
				return 0;
		}
		
		if (flag & CMP_MODE) {
			if (saidx0->mode != IPSEC_MODE_ANY
				&& saidx0->mode != saidx1->mode)
				return 0;
		}
		
		if (key_sockaddrcmp((struct sockaddr *)&saidx0->src,
							(struct sockaddr *)&saidx1->src, flag & CMP_PORT ? 1 : 0) != 0) {
			return 0;
		}
		if (key_sockaddrcmp((struct sockaddr *)&saidx0->dst,
							(struct sockaddr *)&saidx1->dst, flag & CMP_PORT ? 1 : 0) != 0) {
			return 0;
		}
	}
	
	return 1;
}