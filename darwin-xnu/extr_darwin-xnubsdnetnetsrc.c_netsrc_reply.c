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
typedef  int /*<<< orphan*/  v1 ;
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int uint16_t ;
struct netsrc_repv1 {int nrp_flags; int /*<<< orphan*/  nrp_dstprecedence; int /*<<< orphan*/  nrp_dstlabel; int /*<<< orphan*/  nrp_precedence; int /*<<< orphan*/  nrp_label; int /*<<< orphan*/  nrp_src; } ;
struct netsrc_rep {int nrp_flags; int /*<<< orphan*/  nrp_dstprecedence; int /*<<< orphan*/  nrp_dstlabel; int /*<<< orphan*/  nrp_precedence; int /*<<< orphan*/  nrp_label; int /*<<< orphan*/  nrp_src; } ;
typedef  int /*<<< orphan*/  kern_ctl_ref ;
typedef  int /*<<< orphan*/  errno_t ;

/* Variables and functions */
 int /*<<< orphan*/  CTL_DATA_EOR ; 
 int /*<<< orphan*/  EHOSTUNREACH ; 
 int /*<<< orphan*/  EINVAL ; 
#define  NETSRC_CURVERS 129 
 int NETSRC_FLAG_ROUTEABLE ; 
 int NETSRC_IP6_FLAG_DEPRECATED ; 
 int NETSRC_IP6_FLAG_OPTIMISTIC ; 
 int NETSRC_IP6_FLAG_SECURED ; 
 int NETSRC_IP6_FLAG_TEMPORARY ; 
 int NETSRC_IP6_FLAG_TENTATIVE ; 
#define  NETSRC_VERSION1 128 
 int /*<<< orphan*/  ctl_enqueuedata (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct netsrc_repv1*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static errno_t
netsrc_reply(kern_ctl_ref kctl, uint32_t unit, uint16_t version,
			 struct netsrc_rep *reply)
{
	switch (version) {
		case NETSRC_CURVERS:
			return ctl_enqueuedata(kctl, unit, reply,
								   sizeof(*reply), CTL_DATA_EOR);
		case NETSRC_VERSION1: {
			if ((reply->nrp_flags & NETSRC_FLAG_ROUTEABLE) == 0) {
				return EHOSTUNREACH;
			}
#define NETSRC_FLAG_V1_MASK (NETSRC_IP6_FLAG_TENTATIVE | \
							 NETSRC_IP6_FLAG_TEMPORARY | \
							 NETSRC_IP6_FLAG_DEPRECATED | \
							 NETSRC_IP6_FLAG_OPTIMISTIC | \
							 NETSRC_IP6_FLAG_SECURED)
			struct netsrc_repv1 v1 = {
				.nrp_src = reply->nrp_src,
				.nrp_flags = (reply->nrp_flags & NETSRC_FLAG_V1_MASK),
				.nrp_label = reply->nrp_label,
				.nrp_precedence = reply->nrp_precedence,
				.nrp_dstlabel = reply->nrp_dstlabel,
				.nrp_dstprecedence = reply->nrp_dstprecedence
			};
			return ctl_enqueuedata(kctl, unit, &v1, sizeof(v1), CTL_DATA_EOR);
		}
	}
	return EINVAL;
}