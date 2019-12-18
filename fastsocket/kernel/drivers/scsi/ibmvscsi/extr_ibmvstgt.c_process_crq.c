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
struct viosrp_crq {int valid; int format; } ;
struct vio_port {TYPE_1__* dma_dev; } ;
struct srp_target {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  unit_address; } ;

/* Variables and functions */
#define  VIOSRP_AIX_FORMAT 133 
#define  VIOSRP_INLINE_FORMAT 132 
#define  VIOSRP_LINUX_FORMAT 131 
#define  VIOSRP_MAD_FORMAT 130 
#define  VIOSRP_OS400_FORMAT 129 
#define  VIOSRP_SRP_FORMAT 128 
 int /*<<< orphan*/  dprintk (char*,int,int) ; 
 int /*<<< orphan*/  eprintk (char*,int) ; 
 int /*<<< orphan*/  h_send_crq (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  process_iu (struct viosrp_crq*,struct srp_target*) ; 
 struct vio_port* target_to_port (struct srp_target*) ; 

__attribute__((used)) static void process_crq(struct viosrp_crq *crq,	struct srp_target *target)
{
	struct vio_port *vport = target_to_port(target);
	dprintk("%x %x\n", crq->valid, crq->format);

	switch (crq->valid) {
	case 0xC0:
		/* initialization */
		switch (crq->format) {
		case 0x01:
			h_send_crq(vport->dma_dev->unit_address,
				   0xC002000000000000, 0);
			break;
		case 0x02:
			break;
		default:
			eprintk("Unknown format %u\n", crq->format);
		}
		break;
	case 0xFF:
		/* transport event */
		break;
	case 0x80:
		/* real payload */
		switch (crq->format) {
		case VIOSRP_SRP_FORMAT:
		case VIOSRP_MAD_FORMAT:
			process_iu(crq, target);
			break;
		case VIOSRP_OS400_FORMAT:
		case VIOSRP_AIX_FORMAT:
		case VIOSRP_LINUX_FORMAT:
		case VIOSRP_INLINE_FORMAT:
			eprintk("Unsupported format %u\n", crq->format);
			break;
		default:
			eprintk("Unknown format %u\n", crq->format);
		}
		break;
	default:
		eprintk("unknown message type 0x%02x!?\n", crq->valid);
	}
}