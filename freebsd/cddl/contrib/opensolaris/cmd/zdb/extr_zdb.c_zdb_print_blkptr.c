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
typedef  int /*<<< orphan*/  blkptr_t ;
typedef  int /*<<< orphan*/  blkbuf ;

/* Variables and functions */
 int BP_SPRINTF_LEN ; 
 int ZDB_FLAG_BSWAP ; 
 int /*<<< orphan*/  byteswap_uint64_array (void*,int) ; 
 int /*<<< orphan*/  printf (char*,char*) ; 
 int /*<<< orphan*/  snprintf_blkptr (char*,int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
zdb_print_blkptr(blkptr_t *bp, int flags)
{
	char blkbuf[BP_SPRINTF_LEN];

	if (flags & ZDB_FLAG_BSWAP)
		byteswap_uint64_array((void *)bp, sizeof (blkptr_t));

	snprintf_blkptr(blkbuf, sizeof (blkbuf), bp);
	(void) printf("%s\n", blkbuf);
}