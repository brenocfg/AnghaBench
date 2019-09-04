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
struct TYPE_2__ {struct buf* le_next; struct buf** le_prev; } ;
struct buf {TYPE_1__ b_hash; } ;
typedef  struct buf* buf_t ;

/* Variables and functions */
 int /*<<< orphan*/  panic (char*) ; 

__attribute__((used)) static __inline__ void 
bremhash(buf_t	bp) 
{
	if (bp->b_hash.le_prev == (struct buf **)0xdeadbeef) 
		panic("bremhash le_prev is deadbeef");
	if (bp->b_hash.le_next == bp) 
		panic("bremhash: next points to self");

	if (bp->b_hash.le_next != NULL)
		bp->b_hash.le_next->b_hash.le_prev = bp->b_hash.le_prev;
	*bp->b_hash.le_prev = (bp)->b_hash.le_next;
}