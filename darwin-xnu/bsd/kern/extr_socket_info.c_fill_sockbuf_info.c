#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int u_int32_t ;
struct sockbuf_info {int sbi_timeo; int /*<<< orphan*/  sbi_flags; int /*<<< orphan*/  sbi_lowat; int /*<<< orphan*/  sbi_mbmax; int /*<<< orphan*/  sbi_mbcnt; int /*<<< orphan*/  sbi_hiwat; int /*<<< orphan*/  sbi_cc; } ;
struct TYPE_2__ {int tv_sec; int tv_usec; } ;
struct sockbuf {TYPE_1__ sb_timeo; int /*<<< orphan*/  sb_flags; int /*<<< orphan*/  sb_lowat; int /*<<< orphan*/  sb_mbmax; int /*<<< orphan*/  sb_mbcnt; int /*<<< orphan*/  sb_hiwat; int /*<<< orphan*/  sb_cc; } ;

/* Variables and functions */
 int hz ; 
 int tick ; 

__attribute__((used)) static void
fill_sockbuf_info(struct sockbuf *sb, struct sockbuf_info *sbi)
{
	sbi->sbi_cc = sb->sb_cc;
	sbi->sbi_hiwat = sb->sb_hiwat;
	sbi->sbi_mbcnt = sb->sb_mbcnt;
	sbi->sbi_mbmax = sb->sb_mbmax;
	sbi->sbi_lowat = sb->sb_lowat;
	sbi->sbi_flags = sb->sb_flags;
	sbi->sbi_timeo = (u_int32_t)(sb->sb_timeo.tv_sec * hz) +
	    sb->sb_timeo.tv_usec / tick;
	if (sbi->sbi_timeo == 0 && sb->sb_timeo.tv_usec != 0)
		sbi->sbi_timeo = 1;
}