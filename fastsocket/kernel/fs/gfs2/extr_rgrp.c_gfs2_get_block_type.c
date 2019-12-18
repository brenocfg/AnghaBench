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
struct gfs2_rgrpd {int dummy; } ;
struct gfs2_rbm {struct gfs2_rgrpd* rgd; } ;

/* Variables and functions */
 int /*<<< orphan*/  WARN_ON_ONCE (int) ; 
 int gfs2_rbm_from_block (struct gfs2_rbm*,int /*<<< orphan*/ ) ; 
 unsigned char gfs2_testbit (struct gfs2_rbm*) ; 

__attribute__((used)) static unsigned char gfs2_get_block_type(struct gfs2_rgrpd *rgd, u64 block)
{
	struct gfs2_rbm rbm = { .rgd = rgd, };
	int ret;

	ret = gfs2_rbm_from_block(&rbm, block);
	WARN_ON_ONCE(ret != 0);

	return gfs2_testbit(&rbm);
}