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
struct TYPE_3__ {int max_unaligned_load; int /*<<< orphan*/  (* blkstore ) (int,int,int,int) ;int /*<<< orphan*/  (* blkfetch ) (int,int,int,int) ;} ;
struct TYPE_4__ {TYPE_1__ x; } ;

/* Variables and functions */
 TYPE_2__* IR ; 
 int /*<<< orphan*/  assert (int) ; 
 int dalign ; 
 int salign ; 
 int /*<<< orphan*/  stub1 (int,int,int,int) ; 
 int /*<<< orphan*/  stub2 (int,int,int,int) ; 
 int /*<<< orphan*/  stub3 (int,int,int,int) ; 
 int /*<<< orphan*/  stub4 (int,int,int,int) ; 
 int /*<<< orphan*/  stub5 (int,int,int,int) ; 
 int /*<<< orphan*/  stub6 (int,int,int,int) ; 

__attribute__((used)) static void blkunroll(int k, int dreg, int doff, int sreg, int soff, int size, int tmp[]) {
	int i;

	assert(IR->x.max_unaligned_load);
	if (k > IR->x.max_unaligned_load
	&& (k > salign || k > dalign))
		k = IR->x.max_unaligned_load;
	for (i = 0; i+k < size; i += 2*k) {
		(*IR->x.blkfetch)(k, soff+i,   sreg, tmp[0]);
		(*IR->x.blkfetch)(k, soff+i+k, sreg, tmp[1]);
		(*IR->x.blkstore)(k, doff+i,   dreg, tmp[0]);
		(*IR->x.blkstore)(k, doff+i+k, dreg, tmp[1]);
	}
	if (i < size) {
		(*IR->x.blkfetch)(k, i+soff, sreg, tmp[0]);
		(*IR->x.blkstore)(k, i+doff, dreg, tmp[0]);
	}
}