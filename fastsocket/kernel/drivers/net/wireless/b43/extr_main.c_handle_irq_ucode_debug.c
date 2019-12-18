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
typedef  int u16 ;
struct TYPE_2__ {int /*<<< orphan*/  opensource; } ;
struct b43_wldev {int /*<<< orphan*/  wl; TYPE_1__ fw; } ;
typedef  int /*<<< orphan*/  __le16 ;

/* Variables and functions */
 int /*<<< orphan*/  B43_DEBUG ; 
 int /*<<< orphan*/  B43_DEBUGIRQ_ACK ; 
#define  B43_DEBUGIRQ_DUMP_REGS 131 
#define  B43_DEBUGIRQ_DUMP_SHM 130 
#define  B43_DEBUGIRQ_MARKER 129 
#define  B43_DEBUGIRQ_PANIC 128 
 unsigned int B43_DEBUGIRQ_REASON_REG ; 
 unsigned int B43_MARKER_ID_REG ; 
 unsigned int B43_MARKER_LINE_REG ; 
 int /*<<< orphan*/  B43_SHM_SCRATCH ; 
 int /*<<< orphan*/  B43_SHM_SHARED ; 
 int /*<<< orphan*/  DUMP_PREFIX_OFFSET ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 char* KERN_INFO ; 
 int /*<<< orphan*/  b43_handle_firmware_panic (struct b43_wldev*) ; 
 int b43_shm_read16 (struct b43_wldev*,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  b43_shm_write16 (struct b43_wldev*,int /*<<< orphan*/ ,unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  b43dbg (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  b43info (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  cpu_to_le16 (int) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  print_hex_dump (char*,char*,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  printk (char*,...) ; 

__attribute__((used)) static void handle_irq_ucode_debug(struct b43_wldev *dev)
{
	unsigned int i, cnt;
	u16 reason, marker_id, marker_line;
	__le16 *buf;

	/* The proprietary firmware doesn't have this IRQ. */
	if (!dev->fw.opensource)
		return;

	/* Read the register that contains the reason code for this IRQ. */
	reason = b43_shm_read16(dev, B43_SHM_SCRATCH, B43_DEBUGIRQ_REASON_REG);

	switch (reason) {
	case B43_DEBUGIRQ_PANIC:
		b43_handle_firmware_panic(dev);
		break;
	case B43_DEBUGIRQ_DUMP_SHM:
		if (!B43_DEBUG)
			break; /* Only with driver debugging enabled. */
		buf = kmalloc(4096, GFP_ATOMIC);
		if (!buf) {
			b43dbg(dev->wl, "SHM-dump: Failed to allocate memory\n");
			goto out;
		}
		for (i = 0; i < 4096; i += 2) {
			u16 tmp = b43_shm_read16(dev, B43_SHM_SHARED, i);
			buf[i / 2] = cpu_to_le16(tmp);
		}
		b43info(dev->wl, "Shared memory dump:\n");
		print_hex_dump(KERN_INFO, "", DUMP_PREFIX_OFFSET,
			       16, 2, buf, 4096, 1);
		kfree(buf);
		break;
	case B43_DEBUGIRQ_DUMP_REGS:
		if (!B43_DEBUG)
			break; /* Only with driver debugging enabled. */
		b43info(dev->wl, "Microcode register dump:\n");
		for (i = 0, cnt = 0; i < 64; i++) {
			u16 tmp = b43_shm_read16(dev, B43_SHM_SCRATCH, i);
			if (cnt == 0)
				printk(KERN_INFO);
			printk("r%02u: 0x%04X  ", i, tmp);
			cnt++;
			if (cnt == 6) {
				printk("\n");
				cnt = 0;
			}
		}
		printk("\n");
		break;
	case B43_DEBUGIRQ_MARKER:
		if (!B43_DEBUG)
			break; /* Only with driver debugging enabled. */
		marker_id = b43_shm_read16(dev, B43_SHM_SCRATCH,
					   B43_MARKER_ID_REG);
		marker_line = b43_shm_read16(dev, B43_SHM_SCRATCH,
					     B43_MARKER_LINE_REG);
		b43info(dev->wl, "The firmware just executed the MARKER(%u) "
			"at line number %u\n",
			marker_id, marker_line);
		break;
	default:
		b43dbg(dev->wl, "Debug-IRQ triggered for unknown reason: %u\n",
		       reason);
	}
out:
	/* Acknowledge the debug-IRQ, so the firmware can continue. */
	b43_shm_write16(dev, B43_SHM_SCRATCH,
			B43_DEBUGIRQ_REASON_REG, B43_DEBUGIRQ_ACK);
}