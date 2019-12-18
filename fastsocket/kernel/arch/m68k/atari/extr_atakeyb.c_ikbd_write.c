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
typedef  int u_char ;
struct TYPE_2__ {int key_ctrl; int /*<<< orphan*/  key_data; } ;

/* Variables and functions */
 int ACIA_TDRE ; 
 TYPE_1__ acia ; 
 int /*<<< orphan*/  panic (char*) ; 

void ikbd_write(const char *str, int len)
{
	u_char acia_stat;

	if ((len < 1) || (len > 7))
		panic("ikbd: maximum string length exceeded");
	while (len) {
		acia_stat = acia.key_ctrl;
		if (acia_stat & ACIA_TDRE) {
			acia.key_data = *str++;
			len--;
		}
	}
}