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
struct TYPE_2__ {int /*<<< orphan*/  attr_id; } ;
struct ib_sa_mad {TYPE_1__ mad_hdr; } ;
struct ib_device {int dummy; } ;

/* Variables and functions */
#define  IB_SA_ATTR_MC_MEMBER_REC 128 
 int be16_to_cpu (int /*<<< orphan*/ ) ; 
 int mlx4_ib_mcg_multiplex_handler (struct ib_device*,int,int,struct ib_sa_mad*) ; 

__attribute__((used)) static int mlx4_ib_multiplex_sa_handler(struct ib_device *ibdev, int port,
		int slave, struct ib_sa_mad *sa_mad)
{
	int ret = 0;

	/* dispatch to different sa handlers */
	switch (be16_to_cpu(sa_mad->mad_hdr.attr_id)) {
	case IB_SA_ATTR_MC_MEMBER_REC:
		ret = mlx4_ib_mcg_multiplex_handler(ibdev, port, slave, sa_mad);
		break;
	default:
		break;
	}
	return ret;
}