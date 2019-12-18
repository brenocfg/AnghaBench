#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  unsigned int u8 ;
struct gfs2_rbm {int offset; TYPE_2__* bi; } ;
struct TYPE_4__ {int bi_offset; TYPE_1__* bi_bh; } ;
struct TYPE_3__ {unsigned int* b_data; } ;

/* Variables and functions */
 unsigned int const GFS2_BIT_MASK ; 
 int GFS2_BIT_SIZE ; 
 int GFS2_NBBY ; 

__attribute__((used)) static inline u8 gfs2_testbit(const struct gfs2_rbm *rbm)
{
	const u8 *buffer = rbm->bi->bi_bh->b_data + rbm->bi->bi_offset;
	const u8 *byte;
	unsigned int bit;

	byte = buffer + (rbm->offset / GFS2_NBBY);
	bit = (rbm->offset % GFS2_NBBY) * GFS2_BIT_SIZE;

	return (*byte >> bit) & GFS2_BIT_MASK;
}