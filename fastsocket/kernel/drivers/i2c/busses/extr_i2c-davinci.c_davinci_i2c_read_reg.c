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
typedef  int /*<<< orphan*/  u16 ;
struct davinci_i2c_dev {scalar_t__ base; } ;

/* Variables and functions */
 int /*<<< orphan*/  __raw_readw (scalar_t__) ; 

__attribute__((used)) static inline u16 davinci_i2c_read_reg(struct davinci_i2c_dev *i2c_dev, int reg)
{
	return __raw_readw(i2c_dev->base + reg);
}