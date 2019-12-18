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
typedef  int /*<<< orphan*/  u16 ;
struct zd_ioreq16 {int /*<<< orphan*/  value; int /*<<< orphan*/  addr; } ;
struct zd_chip {int /*<<< orphan*/  usb; int /*<<< orphan*/  mutex; } ;

/* Variables and functions */
 int /*<<< orphan*/  ZD_ASSERT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_is_locked (int /*<<< orphan*/ *) ; 
 int zd_usb_iowrite16v (int /*<<< orphan*/ *,struct zd_ioreq16*,int) ; 

__attribute__((used)) static inline int zd_iowrite16_locked(struct zd_chip *chip, u16 value,
	                              zd_addr_t addr)
{
	struct zd_ioreq16 ioreq;

	ZD_ASSERT(mutex_is_locked(&chip->mutex));
	ioreq.addr = addr;
	ioreq.value = value;

	return zd_usb_iowrite16v(&chip->usb, &ioreq, 1);
}