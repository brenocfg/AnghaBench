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
typedef  int /*<<< orphan*/  zd_addr_t ;
typedef  int /*<<< orphan*/  u32 ;
struct zd_ioreq32 {int /*<<< orphan*/  value; int /*<<< orphan*/  addr; } ;
struct zd_chip {int dummy; } ;

/* Variables and functions */
 int _zd_iowrite32v_locked (struct zd_chip*,struct zd_ioreq32*,int) ; 

__attribute__((used)) static inline int zd_iowrite32_locked(struct zd_chip *chip, u32 value,
	                              zd_addr_t addr)
{
	struct zd_ioreq32 ioreq;

	ioreq.addr = addr;
	ioreq.value = value;

	return _zd_iowrite32v_locked(chip, &ioreq, 1);
}