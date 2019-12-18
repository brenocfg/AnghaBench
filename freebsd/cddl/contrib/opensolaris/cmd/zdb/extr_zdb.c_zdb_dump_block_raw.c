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
typedef  int /*<<< orphan*/  uint64_t ;

/* Variables and functions */
 int ZDB_FLAG_BSWAP ; 
 int /*<<< orphan*/  byteswap_uint64_array (void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  write (int,void*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
zdb_dump_block_raw(void *buf, uint64_t size, int flags)
{
	if (flags & ZDB_FLAG_BSWAP)
		byteswap_uint64_array(buf, size);
	(void) write(1, buf, size);
}