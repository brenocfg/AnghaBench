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
typedef  int u32 ;
struct kwqe {int /*<<< orphan*/  kwqe_op_flag; } ;
struct cnic_dev {int /*<<< orphan*/  netdev; int /*<<< orphan*/  flags; } ;
struct bnx2x {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BNX2X_CHIP_IS_E2_PLUS (struct bnx2x*) ; 
 int /*<<< orphan*/  CNIC_F_CNIC_UP ; 
 int EAGAIN ; 
 int EINVAL ; 
 int EIO ; 
#define  FCOE_KWQE_OPCODE_DESTROY 134 
#define  FCOE_KWQE_OPCODE_DESTROY_CONN 133 
#define  FCOE_KWQE_OPCODE_DISABLE_CONN 132 
#define  FCOE_KWQE_OPCODE_ENABLE_CONN 131 
#define  FCOE_KWQE_OPCODE_INIT1 130 
#define  FCOE_KWQE_OPCODE_OFFLOAD_CONN1 129 
#define  FCOE_KWQE_OPCODE_STAT 128 
 int KWQE_OPCODE (int /*<<< orphan*/ ) ; 
 int cnic_bnx2x_fcoe_destroy (struct cnic_dev*,struct kwqe*) ; 
 int cnic_bnx2x_fcoe_disable (struct cnic_dev*,struct kwqe*) ; 
 int cnic_bnx2x_fcoe_enable (struct cnic_dev*,struct kwqe*) ; 
 int cnic_bnx2x_fcoe_fw_destroy (struct cnic_dev*,struct kwqe*) ; 
 int cnic_bnx2x_fcoe_init1 (struct cnic_dev*,struct kwqe**,int,int*) ; 
 int cnic_bnx2x_fcoe_ofld1 (struct cnic_dev*,struct kwqe**,int,int*) ; 
 int cnic_bnx2x_fcoe_stat (struct cnic_dev*,struct kwqe*) ; 
 int /*<<< orphan*/  cnic_bnx2x_kwqe_err (struct cnic_dev*,struct kwqe*) ; 
 int /*<<< orphan*/  netdev_err (int /*<<< orphan*/ ,char*,int) ; 
 struct bnx2x* netdev_priv (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int cnic_submit_bnx2x_fcoe_kwqes(struct cnic_dev *dev,
					struct kwqe *wqes[], u32 num_wqes)
{
	struct bnx2x *bp = netdev_priv(dev->netdev);
	int i, work, ret;
	u32 opcode;
	struct kwqe *kwqe;

	if (!test_bit(CNIC_F_CNIC_UP, &dev->flags))
		return -EAGAIN;		/* bnx2 is down */

	if (!BNX2X_CHIP_IS_E2_PLUS(bp))
		return -EINVAL;

	for (i = 0; i < num_wqes; ) {
		kwqe = wqes[i];
		opcode = KWQE_OPCODE(kwqe->kwqe_op_flag);
		work = 1;

		switch (opcode) {
		case FCOE_KWQE_OPCODE_INIT1:
			ret = cnic_bnx2x_fcoe_init1(dev, &wqes[i],
						    num_wqes - i, &work);
			break;
		case FCOE_KWQE_OPCODE_OFFLOAD_CONN1:
			ret = cnic_bnx2x_fcoe_ofld1(dev, &wqes[i],
						    num_wqes - i, &work);
			break;
		case FCOE_KWQE_OPCODE_ENABLE_CONN:
			ret = cnic_bnx2x_fcoe_enable(dev, kwqe);
			break;
		case FCOE_KWQE_OPCODE_DISABLE_CONN:
			ret = cnic_bnx2x_fcoe_disable(dev, kwqe);
			break;
		case FCOE_KWQE_OPCODE_DESTROY_CONN:
			ret = cnic_bnx2x_fcoe_destroy(dev, kwqe);
			break;
		case FCOE_KWQE_OPCODE_DESTROY:
			ret = cnic_bnx2x_fcoe_fw_destroy(dev, kwqe);
			break;
		case FCOE_KWQE_OPCODE_STAT:
			ret = cnic_bnx2x_fcoe_stat(dev, kwqe);
			break;
		default:
			ret = 0;
			netdev_err(dev->netdev, "Unknown type of KWQE(0x%x)\n",
				   opcode);
			break;
		}
		if (ret < 0) {
			netdev_err(dev->netdev, "KWQE(0x%x) failed\n",
				   opcode);

			/* Possibly bnx2x parity error, send completion
			 * to ulp drivers with error code to speed up
			 * cleanup and reset recovery.
			 */
			if (ret == -EIO || ret == -EAGAIN)
				cnic_bnx2x_kwqe_err(dev, kwqe);
		}
		i += work;
	}
	return 0;
}