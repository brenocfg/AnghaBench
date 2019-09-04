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
typedef  scalar_t__ u_int32_t ;
struct sockbuf {int sb_flags; scalar_t__ sb_idealsize; scalar_t__ sb_hiwat; scalar_t__ sb_cc; } ;

/* Variables and functions */
 int SB_AUTOSIZE ; 
 int SB_TRIM ; 
 int /*<<< orphan*/  sbreserve (struct sockbuf*,scalar_t__) ; 
 int tcp_do_autosendbuf ; 

void
tcp_sbsnd_trim(struct sockbuf *sbsnd)
{
	if (tcp_do_autosendbuf == 1 &&
		((sbsnd->sb_flags & (SB_AUTOSIZE | SB_TRIM)) ==
			(SB_AUTOSIZE | SB_TRIM)) &&
		(sbsnd->sb_idealsize > 0) &&
		(sbsnd->sb_hiwat > sbsnd->sb_idealsize)) {
		u_int32_t trim = 0;
		if (sbsnd->sb_cc <= sbsnd->sb_idealsize) {
			trim = sbsnd->sb_hiwat - sbsnd->sb_idealsize;
		} else {
			trim = sbsnd->sb_hiwat - sbsnd->sb_cc;
		}
		sbreserve(sbsnd, (sbsnd->sb_hiwat - trim));
	}
	if (sbsnd->sb_hiwat <= sbsnd->sb_idealsize)
		sbsnd->sb_flags &= ~(SB_TRIM);
}