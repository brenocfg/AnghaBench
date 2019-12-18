#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {scalar_t__ ub_checkpoint_txg; int /*<<< orphan*/  ub_rootbp; scalar_t__ ub_timestamp; scalar_t__ ub_guid_sum; scalar_t__ ub_txg; scalar_t__ ub_version; scalar_t__ ub_magic; } ;
typedef  TYPE_1__ uberblock_t ;
typedef  char const* u_longlong_t ;
typedef  scalar_t__ time_t ;
typedef  int /*<<< orphan*/  blkbuf ;

/* Variables and functions */
 int BP_SPRINTF_LEN ; 
 int /*<<< orphan*/  asctime (int /*<<< orphan*/ ) ; 
 int* dump_opt ; 
 int /*<<< orphan*/  localtime (scalar_t__*) ; 
 int /*<<< orphan*/  printf (char*,char const*,...) ; 
 int /*<<< orphan*/  snprintf_blkptr (char*,int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
dump_uberblock(uberblock_t *ub, const char *header, const char *footer)
{
	time_t timestamp = ub->ub_timestamp;

	(void) printf("%s", header ? header : "");
	(void) printf("\tmagic = %016llx\n", (u_longlong_t)ub->ub_magic);
	(void) printf("\tversion = %llu\n", (u_longlong_t)ub->ub_version);
	(void) printf("\ttxg = %llu\n", (u_longlong_t)ub->ub_txg);
	(void) printf("\tguid_sum = %llu\n", (u_longlong_t)ub->ub_guid_sum);
	(void) printf("\ttimestamp = %llu UTC = %s",
	    (u_longlong_t)ub->ub_timestamp, asctime(localtime(&timestamp)));
	if (dump_opt['u'] >= 3) {
		char blkbuf[BP_SPRINTF_LEN];
		snprintf_blkptr(blkbuf, sizeof (blkbuf), &ub->ub_rootbp);
		(void) printf("\trootbp = %s\n", blkbuf);
	}
	(void) printf("\tcheckpoint_txg = %llu\n",
	    (u_longlong_t)ub->ub_checkpoint_txg);
	(void) printf("%s", footer ? footer : "");
}