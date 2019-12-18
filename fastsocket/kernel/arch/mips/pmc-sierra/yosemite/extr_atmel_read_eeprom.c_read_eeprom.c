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

/* Variables and functions */
 int R_HEADER ; 
 int W_HEADER ; 
 int recv_ack () ; 
 int /*<<< orphan*/  recv_byte () ; 
 int /*<<< orphan*/  send_ack () ; 
 int /*<<< orphan*/  send_byte (int) ; 
 int /*<<< orphan*/  send_start () ; 
 int /*<<< orphan*/  send_stop () ; 

int read_eeprom(char *buffer, int eeprom_size, int size)
{
	int	i = 0, err;

	send_start();
	send_byte(W_HEADER);
	recv_ack();

	/* EEPROM with size of more than 2K need two byte addressing */
	if (eeprom_size > 2048) {
		send_byte(0x00);
		recv_ack();
	}

	send_start();
	send_byte(R_HEADER);
	err = recv_ack();
	if (err == -1)
		return err;

	for (i = 0; i < size; i++) {
		*buffer++ = recv_byte();
		send_ack();
	}

	/* Note : We should do some check if the buffer contains correct information */

	send_stop();
}