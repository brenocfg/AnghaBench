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
typedef  int /*<<< orphan*/  u32 ;
struct rt2x00_field32 {int dummy; } ;
struct rt2x00_dev {TYPE_1__* ops; } ;
struct rt2800_ops {int (* regbusy_read ) (struct rt2x00_dev*,unsigned int const,struct rt2x00_field32 const,int /*<<< orphan*/ *) ;} ;
struct TYPE_2__ {struct rt2800_ops* drv; } ;

/* Variables and functions */
 int stub1 (struct rt2x00_dev*,unsigned int const,struct rt2x00_field32 const,int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline int rt2800_regbusy_read(struct rt2x00_dev *rt2x00dev,
				      const unsigned int offset,
				      const struct rt2x00_field32 field,
				      u32 *reg)
{
	const struct rt2800_ops *rt2800ops = rt2x00dev->ops->drv;

	return rt2800ops->regbusy_read(rt2x00dev, offset, field, reg);
}