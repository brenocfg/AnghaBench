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
 int EIO ; 
 int card_send_command (int const*,char const*,unsigned char const*,unsigned char*) ; 
 int sb1000_end_get_set_command (int const*,char const*) ; 
 int sb1000_start_get_set_command (int const*,char const*) ; 

__attribute__((used)) static int
sb1000_get_firmware_version(const int ioaddr[], const char* name,
	unsigned char version[], int do_end)
{
	static const unsigned char Command0[6] = {0x80, 0x23, 0x00, 0x00, 0x00, 0x00};

	unsigned char st[7];
	int status;

	if ((status = sb1000_start_get_set_command(ioaddr, name)))
		return status;
	if ((status = card_send_command(ioaddr, name, Command0, st)))
		return status;
	if (st[0] != 0xa3)
		return -EIO;
	version[0] = st[1];
	version[1] = st[2];
	if (do_end)
		return sb1000_end_get_set_command(ioaddr, name);
	else
		return 0;
}