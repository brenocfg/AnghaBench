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
typedef  int /*<<< orphan*/  syswd_t ;
typedef  int /*<<< orphan*/  (* dvdcallbacklow ) (int) ;

/* Variables and functions */
 int /*<<< orphan*/  IRQMASK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IRQ_PI_DI ; 
 int /*<<< orphan*/  __MaskIrq (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __dvd_callback (int) ; 

__attribute__((used)) static void __dvd_timeouthandler(syswd_t alarm,void *cbarg)
{
	dvdcallbacklow cb;

	__MaskIrq(IRQMASK(IRQ_PI_DI));
	cb = __dvd_callback;
	if(cb) cb(0x10);
}