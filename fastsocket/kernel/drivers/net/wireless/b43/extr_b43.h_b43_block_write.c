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
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u16 ;
struct b43_wldev {TYPE_1__* dev; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* block_write ) (TYPE_1__*,void const*,size_t,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (TYPE_1__*,void const*,size_t,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void b43_block_write(struct b43_wldev *dev, const void *buffer,
				   size_t count, u16 offset, u8 reg_width)
{
	dev->dev->block_write(dev->dev, buffer, count, offset, reg_width);
}