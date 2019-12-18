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
struct TYPE_2__ {int /*<<< orphan*/  pullup_pin; int /*<<< orphan*/  pullup_active_low; } ;
struct at91_udc {TYPE_1__ board; int /*<<< orphan*/  vbus; int /*<<< orphan*/  enabled; } ;

/* Variables and functions */
 int /*<<< orphan*/  AT91_MATRIX_USBPUCR ; 
 int /*<<< orphan*/  AT91_MATRIX_USBPUCR_PUON ; 
 int /*<<< orphan*/  AT91_UDP_ICR ; 
 int /*<<< orphan*/  AT91_UDP_IDR ; 
 int /*<<< orphan*/  AT91_UDP_RXRSM ; 
 int /*<<< orphan*/  AT91_UDP_TXVC ; 
 int /*<<< orphan*/  AT91_UDP_TXVC_PUON ; 
 int /*<<< orphan*/  AT91_UDP_TXVC_TXVDIS ; 
 int /*<<< orphan*/  DBG (char*,char*) ; 
 int /*<<< orphan*/  at91_sys_read (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  at91_sys_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  at91_udp_read (struct at91_udc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  at91_udp_write (struct at91_udc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clk_off (struct at91_udc*) ; 
 int /*<<< orphan*/  clk_on (struct at91_udc*) ; 
 scalar_t__ cpu_is_at91rm9200 () ; 
 scalar_t__ cpu_is_at91sam9260 () ; 
 scalar_t__ cpu_is_at91sam9261 () ; 
 scalar_t__ cpu_is_at91sam9263 () ; 
 scalar_t__ cpu_is_at91sam9g20 () ; 
 int /*<<< orphan*/  gpio_set_value (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stop_activity (struct at91_udc*) ; 

__attribute__((used)) static void pullup(struct at91_udc *udc, int is_on)
{
	int	active = !udc->board.pullup_active_low;

	if (!udc->enabled || !udc->vbus)
		is_on = 0;
	DBG("%sactive\n", is_on ? "" : "in");

	if (is_on) {
		clk_on(udc);
		at91_udp_write(udc, AT91_UDP_ICR, AT91_UDP_RXRSM);
		at91_udp_write(udc, AT91_UDP_TXVC, 0);
		if (cpu_is_at91rm9200())
			gpio_set_value(udc->board.pullup_pin, active);
		else if (cpu_is_at91sam9260() || cpu_is_at91sam9263() || cpu_is_at91sam9g20()) {
			u32	txvc = at91_udp_read(udc, AT91_UDP_TXVC);

			txvc |= AT91_UDP_TXVC_PUON;
			at91_udp_write(udc, AT91_UDP_TXVC, txvc);
		} else if (cpu_is_at91sam9261()) {
			u32	usbpucr;

			usbpucr = at91_sys_read(AT91_MATRIX_USBPUCR);
			usbpucr |= AT91_MATRIX_USBPUCR_PUON;
			at91_sys_write(AT91_MATRIX_USBPUCR, usbpucr);
		}
	} else {
		stop_activity(udc);
		at91_udp_write(udc, AT91_UDP_IDR, AT91_UDP_RXRSM);
		at91_udp_write(udc, AT91_UDP_TXVC, AT91_UDP_TXVC_TXVDIS);
		if (cpu_is_at91rm9200())
			gpio_set_value(udc->board.pullup_pin, !active);
		else if (cpu_is_at91sam9260() || cpu_is_at91sam9263() || cpu_is_at91sam9g20()) {
			u32	txvc = at91_udp_read(udc, AT91_UDP_TXVC);

			txvc &= ~AT91_UDP_TXVC_PUON;
			at91_udp_write(udc, AT91_UDP_TXVC, txvc);
		} else if (cpu_is_at91sam9261()) {
			u32	usbpucr;

			usbpucr = at91_sys_read(AT91_MATRIX_USBPUCR);
			usbpucr &= ~AT91_MATRIX_USBPUCR_PUON;
			at91_sys_write(AT91_MATRIX_USBPUCR, usbpucr);
		}
		clk_off(udc);
	}
}