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
typedef  int /*<<< orphan*/  u_int ;
struct buf {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MAXPHYS ; 
 int /*<<< orphan*/  buf_count (struct buf*) ; 
 int /*<<< orphan*/  buf_setcount (struct buf*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  min (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

u_int
minphys(struct buf *bp)
{

	buf_setcount(bp, min(MAXPHYS, buf_count(bp)));
        return buf_count(bp);
}