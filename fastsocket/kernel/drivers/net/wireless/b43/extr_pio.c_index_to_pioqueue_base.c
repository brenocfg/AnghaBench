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
typedef  int /*<<< orphan*/  const u16 ;
struct b43_wldev {TYPE_1__* dev; } ;
struct TYPE_2__ {int core_rev; } ;

/* Variables and functions */
 unsigned int ARRAY_SIZE (int /*<<< orphan*/  const*) ; 
#define  B43_MMIO_PIO11_BASE0 141 
#define  B43_MMIO_PIO11_BASE1 140 
#define  B43_MMIO_PIO11_BASE2 139 
#define  B43_MMIO_PIO11_BASE3 138 
#define  B43_MMIO_PIO11_BASE4 137 
#define  B43_MMIO_PIO11_BASE5 136 
#define  B43_MMIO_PIO_BASE0 135 
#define  B43_MMIO_PIO_BASE1 134 
#define  B43_MMIO_PIO_BASE2 133 
#define  B43_MMIO_PIO_BASE3 132 
#define  B43_MMIO_PIO_BASE4 131 
#define  B43_MMIO_PIO_BASE5 130 
#define  B43_MMIO_PIO_BASE6 129 
#define  B43_MMIO_PIO_BASE7 128 
 int /*<<< orphan*/  B43_WARN_ON (int) ; 

__attribute__((used)) static u16 index_to_pioqueue_base(struct b43_wldev *dev,
				  unsigned int index)
{
	static const u16 bases[] = {
		B43_MMIO_PIO_BASE0,
		B43_MMIO_PIO_BASE1,
		B43_MMIO_PIO_BASE2,
		B43_MMIO_PIO_BASE3,
		B43_MMIO_PIO_BASE4,
		B43_MMIO_PIO_BASE5,
		B43_MMIO_PIO_BASE6,
		B43_MMIO_PIO_BASE7,
	};
	static const u16 bases_rev11[] = {
		B43_MMIO_PIO11_BASE0,
		B43_MMIO_PIO11_BASE1,
		B43_MMIO_PIO11_BASE2,
		B43_MMIO_PIO11_BASE3,
		B43_MMIO_PIO11_BASE4,
		B43_MMIO_PIO11_BASE5,
	};

	if (dev->dev->core_rev >= 11) {
		B43_WARN_ON(index >= ARRAY_SIZE(bases_rev11));
		return bases_rev11[index];
	}
	B43_WARN_ON(index >= ARRAY_SIZE(bases));
	return bases[index];
}