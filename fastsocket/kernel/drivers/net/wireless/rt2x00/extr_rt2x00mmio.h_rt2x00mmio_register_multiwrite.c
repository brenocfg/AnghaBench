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
typedef  int u32 ;
struct TYPE_2__ {scalar_t__ base; } ;
struct rt2x00_dev {TYPE_1__ csr; } ;

/* Variables and functions */
 int /*<<< orphan*/  __iowrite32_copy (scalar_t__,void const*,int const) ; 

__attribute__((used)) static inline void rt2x00mmio_register_multiwrite(struct rt2x00_dev *rt2x00dev,
						  const unsigned int offset,
						  const void *value,
						  const u32 length)
{
	__iowrite32_copy(rt2x00dev->csr.base + offset, value, length >> 2);
}