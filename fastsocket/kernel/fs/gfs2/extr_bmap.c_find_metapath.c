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
typedef  int /*<<< orphan*/  u64 ;
struct metapath {int /*<<< orphan*/ * mp_list; } ;
struct gfs2_sbd {int /*<<< orphan*/  sd_inptrs; } ;

/* Variables and functions */
 int /*<<< orphan*/  do_div (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void find_metapath(const struct gfs2_sbd *sdp, u64 block,
			  struct metapath *mp, unsigned int height)
{
	unsigned int i;

	for (i = height; i--;)
		mp->mp_list[i] = do_div(block, sdp->sd_inptrs);

}