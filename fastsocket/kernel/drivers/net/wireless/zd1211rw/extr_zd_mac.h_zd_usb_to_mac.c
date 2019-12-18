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
struct zd_usb {int dummy; } ;
struct zd_mac {int dummy; } ;

/* Variables and functions */
 struct zd_mac* zd_chip_to_mac (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zd_usb_to_chip (struct zd_usb*) ; 

__attribute__((used)) static inline struct zd_mac *zd_usb_to_mac(struct zd_usb *usb)
{
	return zd_chip_to_mac(zd_usb_to_chip(usb));
}