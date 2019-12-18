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
typedef  scalar_t__ u32 ;
struct hermes {int dummy; } ;

/* Variables and functions */
 scalar_t__ MAX_DL_SIZE ; 
 int ezusb_program_bytes (struct hermes*,char const*,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  pr_debug (char*,scalar_t__,scalar_t__,char const*) ; 

__attribute__((used)) static int ezusb_program(struct hermes *hw, const char *buf,
			 u32 addr, u32 len)
{
	u32 ch_addr;
	u32 ch_len;
	int err = 0;

	/* We can only send 2048 bytes out of the bulk xmit at a time,
	 * so we have to split any programming into chunks of <2048
	 * bytes. */

	ch_len = (len < MAX_DL_SIZE) ? len : MAX_DL_SIZE;
	ch_addr = addr;

	while (ch_addr < (addr + len)) {
		pr_debug("Programming subblock of length %d "
			 "to address 0x%08x. Data @ %p\n",
			 ch_len, ch_addr, &buf[ch_addr - addr]);

		err = ezusb_program_bytes(hw, &buf[ch_addr - addr],
					  ch_addr, ch_len);
		if (err)
			break;

		ch_addr += ch_len;
		ch_len = ((addr + len - ch_addr) < MAX_DL_SIZE) ?
			(addr + len - ch_addr) : MAX_DL_SIZE;
	}

	return err;
}