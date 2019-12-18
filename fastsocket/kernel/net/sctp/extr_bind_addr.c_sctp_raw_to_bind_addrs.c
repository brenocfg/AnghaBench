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
typedef  union sctp_addr_param {int dummy; } sctp_addr_param ;
typedef  union sctp_addr {int dummy; } sctp_addr ;
struct sctp_paramhdr {int /*<<< orphan*/  length; int /*<<< orphan*/  type; } ;
struct sctp_bind_addr {int dummy; } ;
struct sctp_af {int /*<<< orphan*/  (* from_addr_param ) (union sctp_addr*,union sctp_addr_param*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;
typedef  int /*<<< orphan*/  gfp_t ;
typedef  int /*<<< orphan*/  __u8 ;
typedef  int /*<<< orphan*/  __u16 ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  SCTP_ADDR_SRC ; 
 int /*<<< orphan*/  htons (int /*<<< orphan*/ ) ; 
 int ntohs (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  param_type2af (int /*<<< orphan*/ ) ; 
 int sctp_add_bind_addr (struct sctp_bind_addr*,union sctp_addr*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sctp_bind_addr_clean (struct sctp_bind_addr*) ; 
 struct sctp_af* sctp_get_af_specific (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (union sctp_addr*,union sctp_addr_param*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int) ; 

int sctp_raw_to_bind_addrs(struct sctp_bind_addr *bp, __u8 *raw_addr_list,
			   int addrs_len, __u16 port, gfp_t gfp)
{
	union sctp_addr_param *rawaddr;
	struct sctp_paramhdr *param;
	union sctp_addr addr;
	int retval = 0;
	int len;
	struct sctp_af *af;

	/* Convert the raw address to standard address format */
	while (addrs_len) {
		param = (struct sctp_paramhdr *)raw_addr_list;
		rawaddr = (union sctp_addr_param *)raw_addr_list;

		af = sctp_get_af_specific(param_type2af(param->type));
		if (unlikely(!af)) {
			retval = -EINVAL;
			sctp_bind_addr_clean(bp);
			break;
		}

		af->from_addr_param(&addr, rawaddr, htons(port), 0);
		retval = sctp_add_bind_addr(bp, &addr, SCTP_ADDR_SRC, gfp);
		if (retval) {
			/* Can't finish building the list, clean up. */
			sctp_bind_addr_clean(bp);
			break;
		}

		len = ntohs(param->length);
		addrs_len -= len;
		raw_addr_list += len;
	}

	return retval;
}