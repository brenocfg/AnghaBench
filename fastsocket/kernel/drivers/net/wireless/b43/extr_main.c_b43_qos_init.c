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
struct b43_wldev {int /*<<< orphan*/  wl; int /*<<< orphan*/  qos_enabled; } ;

/* Variables and functions */
 int B43_HF_EDCF ; 
 int /*<<< orphan*/  B43_MMIO_IFSCTL ; 
 int B43_MMIO_IFSCTL_USE_EDCF ; 
 int b43_hf_read (struct b43_wldev*) ; 
 int /*<<< orphan*/  b43_hf_write (struct b43_wldev*,int) ; 
 int /*<<< orphan*/  b43_qos_upload_all (struct b43_wldev*) ; 
 int b43_read16 (struct b43_wldev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  b43_write16 (struct b43_wldev*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  b43dbg (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static void b43_qos_init(struct b43_wldev *dev)
{
	if (!dev->qos_enabled) {
		/* Disable QOS support. */
		b43_hf_write(dev, b43_hf_read(dev) & ~B43_HF_EDCF);
		b43_write16(dev, B43_MMIO_IFSCTL,
			    b43_read16(dev, B43_MMIO_IFSCTL)
			    & ~B43_MMIO_IFSCTL_USE_EDCF);
		b43dbg(dev->wl, "QoS disabled\n");
		return;
	}

	/* Upload the current QOS parameters. */
	b43_qos_upload_all(dev);

	/* Enable QOS support. */
	b43_hf_write(dev, b43_hf_read(dev) | B43_HF_EDCF);
	b43_write16(dev, B43_MMIO_IFSCTL,
		    b43_read16(dev, B43_MMIO_IFSCTL)
		    | B43_MMIO_IFSCTL_USE_EDCF);
	b43dbg(dev->wl, "QoS enabled\n");
}