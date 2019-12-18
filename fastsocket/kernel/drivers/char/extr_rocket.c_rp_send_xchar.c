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
struct tty_struct {struct r_port* driver_data; } ;
struct r_port {int /*<<< orphan*/  channel; } ;
typedef  int /*<<< orphan*/  CHANNEL_t ;

/* Variables and functions */
 scalar_t__ rocket_paranoia_check (struct r_port*,char*) ; 
 scalar_t__ sGetTxCnt (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sGetTxRxDataIO (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sWriteTxByte (int /*<<< orphan*/ ,char) ; 
 int /*<<< orphan*/  sWriteTxPrioByte (int /*<<< orphan*/ *,char) ; 

__attribute__((used)) static void rp_send_xchar(struct tty_struct *tty, char ch)
{
	struct r_port *info = tty->driver_data;
	CHANNEL_t *cp;

	if (rocket_paranoia_check(info, "rp_send_xchar"))
		return;

	cp = &info->channel;
	if (sGetTxCnt(cp))
		sWriteTxPrioByte(cp, ch);
	else
		sWriteTxByte(sGetTxRxDataIO(cp), ch);
}