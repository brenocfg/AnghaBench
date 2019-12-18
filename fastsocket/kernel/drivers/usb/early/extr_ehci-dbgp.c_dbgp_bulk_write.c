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
typedef  int /*<<< orphan*/  u32 ;

/* Variables and functions */
 int /*<<< orphan*/  DBGP_EPADDR (unsigned int,unsigned int) ; 
 int DBGP_ERR_BAD ; 
 int DBGP_MAX_PACKET ; 
 int dbgp_out (int /*<<< orphan*/ ,char const*,int) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static int dbgp_bulk_write(unsigned devnum, unsigned endpoint,
			 const char *bytes, int size)
{
	int ret;
	int loops = 5;
	u32 addr;
	if (size > DBGP_MAX_PACKET)
		return -1;

	addr = DBGP_EPADDR(devnum, endpoint);
try_again:
	if (loops--) {
		ret = dbgp_out(addr, bytes, size);
		if (ret == -DBGP_ERR_BAD) {
			int try_loops = 3;
			do {
				/* Emit a dummy packet to re-sync communication
				 * with the debug device */
				if (dbgp_out(addr, "12345678", 8) >= 0) {
					udelay(2);
					goto try_again;
				}
			} while (try_loops--);
		}
	}

	return ret;
}