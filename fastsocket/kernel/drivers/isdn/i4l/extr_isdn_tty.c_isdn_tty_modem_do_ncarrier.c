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
typedef  int /*<<< orphan*/  modem_info ;

/* Variables and functions */
 int /*<<< orphan*/  RESULT_NO_CARRIER ; 
 int /*<<< orphan*/  isdn_tty_modem_result (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
isdn_tty_modem_do_ncarrier(unsigned long data)
{
	modem_info *info = (modem_info *) data;
	isdn_tty_modem_result(RESULT_NO_CARRIER, info);
}