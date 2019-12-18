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
typedef  enum ib_qp_type { ____Placeholder_ib_qp_type } ib_qp_type ;

/* Variables and functions */
 int EINVAL ; 
#define  IB_QPT_GSI 134 
#define  IB_QPT_RAW_ETHERTYPE 133 
#define  IB_QPT_RAW_IPV6 132 
#define  IB_QPT_RC 131 
#define  IB_QPT_SMI 130 
#define  IB_QPT_UC 129 
#define  IB_QPT_UD 128 
 int ST_RC ; 
 int ST_UC ; 
 int ST_UD ; 
 int /*<<< orphan*/  ehca_gen_err (char*,int) ; 

__attribute__((used)) static inline int ibqptype2servicetype(enum ib_qp_type ibqptype)
{
	switch (ibqptype) {
	case IB_QPT_SMI:
	case IB_QPT_GSI:
		return ST_UD;
	case IB_QPT_RC:
		return ST_RC;
	case IB_QPT_UC:
		return ST_UC;
	case IB_QPT_UD:
		return ST_UD;
	case IB_QPT_RAW_IPV6:
		return -EINVAL;
	case IB_QPT_RAW_ETHERTYPE:
		return -EINVAL;
	default:
		ehca_gen_err("Invalid ibqptype=%x", ibqptype);
		return -EINVAL;
	}
}