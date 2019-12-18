#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
struct TYPE_9__ {int waiting; int /*<<< orphan*/  chipset; } ;
typedef  TYPE_2__ drm_savage_private_t ;
struct TYPE_8__ {unsigned int count; unsigned int start; scalar_t__ global; } ;
struct TYPE_10__ {TYPE_1__ state; } ;
typedef  TYPE_3__ drm_savage_cmd_header_t ;

/* Variables and functions */
 int BCI_CMD_WAIT ; 
 int BCI_CMD_WAIT_3D ; 
 int /*<<< orphan*/  BEGIN_DMA (unsigned int) ; 
 int /*<<< orphan*/  DMA_COMMIT () ; 
 int /*<<< orphan*/  DMA_COPY (int /*<<< orphan*/  const*,unsigned int) ; 
 int /*<<< orphan*/  DMA_LOCALS ; 
 int /*<<< orphan*/  DMA_SET_REGISTERS (unsigned int,unsigned int) ; 
 int /*<<< orphan*/  DMA_WRITE (int) ; 
 scalar_t__ S3_SAVAGE3D_SERIES (int /*<<< orphan*/ ) ; 
 unsigned int SAVAGE_DRAWCTRL0_S4 ; 
 int SAVAGE_DRAWCTRL1_S4 ; 
 int SAVAGE_SCEND_S3D ; 
 unsigned int SAVAGE_SCSTART_S3D ; 
 int savage_verify_state_s3d (TYPE_2__*,unsigned int,unsigned int,int /*<<< orphan*/  const*) ; 
 int savage_verify_state_s4 (TYPE_2__*,unsigned int,unsigned int,int /*<<< orphan*/  const*) ; 

__attribute__((used)) static int savage_dispatch_state(drm_savage_private_t * dev_priv,
				 const drm_savage_cmd_header_t * cmd_header,
				 const uint32_t *regs)
{
	unsigned int count = cmd_header->state.count;
	unsigned int start = cmd_header->state.start;
	unsigned int count2 = 0;
	unsigned int bci_size;
	int ret;
	DMA_LOCALS;

	if (!count)
		return 0;

	if (S3_SAVAGE3D_SERIES(dev_priv->chipset)) {
		ret = savage_verify_state_s3d(dev_priv, start, count, regs);
		if (ret != 0)
			return ret;
		/* scissor regs are emitted in savage_dispatch_draw */
		if (start < SAVAGE_SCSTART_S3D) {
			if (start + count > SAVAGE_SCEND_S3D + 1)
				count2 = count - (SAVAGE_SCEND_S3D + 1 - start);
			if (start + count > SAVAGE_SCSTART_S3D)
				count = SAVAGE_SCSTART_S3D - start;
		} else if (start <= SAVAGE_SCEND_S3D) {
			if (start + count > SAVAGE_SCEND_S3D + 1) {
				count -= SAVAGE_SCEND_S3D + 1 - start;
				start = SAVAGE_SCEND_S3D + 1;
			} else
				return 0;
		}
	} else {
		ret = savage_verify_state_s4(dev_priv, start, count, regs);
		if (ret != 0)
			return ret;
		/* scissor regs are emitted in savage_dispatch_draw */
		if (start < SAVAGE_DRAWCTRL0_S4) {
			if (start + count > SAVAGE_DRAWCTRL1_S4 + 1)
				count2 = count -
					 (SAVAGE_DRAWCTRL1_S4 + 1 - start);
			if (start + count > SAVAGE_DRAWCTRL0_S4)
				count = SAVAGE_DRAWCTRL0_S4 - start;
		} else if (start <= SAVAGE_DRAWCTRL1_S4) {
			if (start + count > SAVAGE_DRAWCTRL1_S4 + 1) {
				count -= SAVAGE_DRAWCTRL1_S4 + 1 - start;
				start = SAVAGE_DRAWCTRL1_S4 + 1;
			} else
				return 0;
		}
	}

	bci_size = count + (count + 254) / 255 + count2 + (count2 + 254) / 255;

	if (cmd_header->state.global) {
		BEGIN_DMA(bci_size + 1);
		DMA_WRITE(BCI_CMD_WAIT | BCI_CMD_WAIT_3D);
		dev_priv->waiting = 1;
	} else {
		BEGIN_DMA(bci_size);
	}

	do {
		while (count > 0) {
			unsigned int n = count < 255 ? count : 255;
			DMA_SET_REGISTERS(start, n);
			DMA_COPY(regs, n);
			count -= n;
			start += n;
			regs += n;
		}
		start += 2;
		regs += 2;
		count = count2;
		count2 = 0;
	} while (count);

	DMA_COMMIT();

	return 0;
}