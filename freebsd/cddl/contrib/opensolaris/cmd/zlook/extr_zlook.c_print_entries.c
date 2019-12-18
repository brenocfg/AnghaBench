#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int zr_bytes; scalar_t__ zr_buf; } ;
typedef  TYPE_1__ zut_readdir_t ;
struct TYPE_5__ {int* d_name; scalar_t__ d_reclen; } ;
typedef  TYPE_2__ dirent64_t ;

/* Variables and functions */
 int DIRENT_NAMELEN (scalar_t__) ; 
 int /*<<< orphan*/  printf (char*,...) ; 

__attribute__((used)) static void
print_entries(zut_readdir_t *r)
{
	dirent64_t *dp;
	char *bufstart;

	dp = (dirent64_t *)(intptr_t)r->zr_buf;
	bufstart = (char *)dp;
	while ((char *)dp < bufstart + r->zr_bytes) {
		int i = 0;
		while (i < DIRENT_NAMELEN(dp->d_reclen)) {
			if (!dp->d_name[i])
				break;
			(void) printf("%c", dp->d_name[i++]);
		}
		(void) printf("\n");
		dp = (dirent64_t *)((intptr_t)dp + dp->d_reclen);
	}
}