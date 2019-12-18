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
struct ql_adapter {int /*<<< orphan*/  ndev; } ;

/* Variables and functions */
 int EINVAL ; 
 int EPERM ; 
 int /*<<< orphan*/  RT_DATA ; 
 int /*<<< orphan*/  RT_IDX ; 
 int RT_IDX_ALLMULTI_SLOT ; 
 int RT_IDX_ALL_ERR_SLOT ; 
#define  RT_IDX_BCAST 136 
 int RT_IDX_BCAST_SLOT ; 
#define  RT_IDX_CAM_HIT 135 
 int RT_IDX_CAM_HIT_SLOT ; 
 int RT_IDX_DST_CAM_Q ; 
 int RT_IDX_DST_DFLT_Q ; 
 int RT_IDX_DST_RSS ; 
 int RT_IDX_E ; 
#define  RT_IDX_ERR 134 
 int RT_IDX_IDX_SHIFT ; 
#define  RT_IDX_IP_CSUM_ERR 133 
 int RT_IDX_IP_CSUM_ERR_SLOT ; 
#define  RT_IDX_MCAST 132 
#define  RT_IDX_MCAST_MATCH 131 
 int RT_IDX_MCAST_MATCH_SLOT ; 
 int /*<<< orphan*/  RT_IDX_MW ; 
 int RT_IDX_PROMISCUOUS_SLOT ; 
#define  RT_IDX_RSS_MATCH 130 
 int RT_IDX_RSS_MATCH_SLOT ; 
 int RT_IDX_TCP_UDP_CSUM_ERR_SLOT ; 
#define  RT_IDX_TU_CSUM_ERR 129 
 int RT_IDX_TYPE_NICQ ; 
#define  RT_IDX_VALID 128 
 int /*<<< orphan*/  ifup ; 
 int /*<<< orphan*/  netif_err (struct ql_adapter*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int) ; 
 int ql_wait_reg_rdy (struct ql_adapter*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ql_write32 (struct ql_adapter*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int ql_set_routing_reg(struct ql_adapter *qdev, u32 index, u32 mask,
			      int enable)
{
	int status = -EINVAL; /* Return error if no mask match. */
	u32 value = 0;

	switch (mask) {
	case RT_IDX_CAM_HIT:
		{
			value = RT_IDX_DST_CAM_Q |	/* dest */
			    RT_IDX_TYPE_NICQ |	/* type */
			    (RT_IDX_CAM_HIT_SLOT << RT_IDX_IDX_SHIFT);/* index */
			break;
		}
	case RT_IDX_VALID:	/* Promiscuous Mode frames. */
		{
			value = RT_IDX_DST_DFLT_Q |	/* dest */
			    RT_IDX_TYPE_NICQ |	/* type */
			    (RT_IDX_PROMISCUOUS_SLOT << RT_IDX_IDX_SHIFT);/* index */
			break;
		}
	case RT_IDX_ERR:	/* Pass up MAC,IP,TCP/UDP error frames. */
		{
			value = RT_IDX_DST_DFLT_Q |	/* dest */
			    RT_IDX_TYPE_NICQ |	/* type */
			    (RT_IDX_ALL_ERR_SLOT << RT_IDX_IDX_SHIFT);/* index */
			break;
		}
	case RT_IDX_IP_CSUM_ERR: /* Pass up IP CSUM error frames. */
		{
			value = RT_IDX_DST_DFLT_Q | /* dest */
				RT_IDX_TYPE_NICQ | /* type */
				(RT_IDX_IP_CSUM_ERR_SLOT <<
				RT_IDX_IDX_SHIFT); /* index */
			break;	
		}
	case RT_IDX_TU_CSUM_ERR: /* Pass up TCP/UDP CSUM error frames. */
		{
			value = RT_IDX_DST_DFLT_Q | /* dest */
				RT_IDX_TYPE_NICQ | /* type */
				(RT_IDX_TCP_UDP_CSUM_ERR_SLOT <<
				RT_IDX_IDX_SHIFT); /* index */
			break;
		}
	case RT_IDX_BCAST:	/* Pass up Broadcast frames to default Q. */
		{
			value = RT_IDX_DST_DFLT_Q |	/* dest */
			    RT_IDX_TYPE_NICQ |	/* type */
			    (RT_IDX_BCAST_SLOT << RT_IDX_IDX_SHIFT);/* index */
			break;
		}
	case RT_IDX_MCAST:	/* Pass up All Multicast frames. */
		{
			value = RT_IDX_DST_DFLT_Q |	/* dest */
			    RT_IDX_TYPE_NICQ |	/* type */
			    (RT_IDX_ALLMULTI_SLOT << RT_IDX_IDX_SHIFT);/* index */
			break;
		}
	case RT_IDX_MCAST_MATCH:	/* Pass up matched Multicast frames. */
		{
			value = RT_IDX_DST_DFLT_Q |	/* dest */
			    RT_IDX_TYPE_NICQ |	/* type */
			    (RT_IDX_MCAST_MATCH_SLOT << RT_IDX_IDX_SHIFT);/* index */
			break;
		}
	case RT_IDX_RSS_MATCH:	/* Pass up matched RSS frames. */
		{
			value = RT_IDX_DST_RSS |	/* dest */
			    RT_IDX_TYPE_NICQ |	/* type */
			    (RT_IDX_RSS_MATCH_SLOT << RT_IDX_IDX_SHIFT);/* index */
			break;
		}
	case 0:		/* Clear the E-bit on an entry. */
		{
			value = RT_IDX_DST_DFLT_Q |	/* dest */
			    RT_IDX_TYPE_NICQ |	/* type */
			    (index << RT_IDX_IDX_SHIFT);/* index */
			break;
		}
	default:
		netif_err(qdev, ifup, qdev->ndev,
			  "Mask type %d not yet supported.\n", mask);
		status = -EPERM;
		goto exit;
	}

	if (value) {
		status = ql_wait_reg_rdy(qdev, RT_IDX, RT_IDX_MW, 0);
		if (status)
			goto exit;
		value |= (enable ? RT_IDX_E : 0);
		ql_write32(qdev, RT_IDX, value);
		ql_write32(qdev, RT_DATA, enable ? mask : 0);
	}
exit:
	return status;
}