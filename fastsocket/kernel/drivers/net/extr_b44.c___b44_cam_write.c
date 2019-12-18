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
typedef  int u32 ;
struct b44 {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  B44_CAM_CTRL ; 
 int /*<<< orphan*/  B44_CAM_DATA_HI ; 
 int /*<<< orphan*/  B44_CAM_DATA_LO ; 
 int /*<<< orphan*/  CAM_CTRL_BUSY ; 
 int CAM_CTRL_INDEX_SHIFT ; 
 int CAM_CTRL_WRITE ; 
 int CAM_DATA_HI_VALID ; 
 int /*<<< orphan*/  b44_wait_bit (struct b44*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  bw32 (struct b44*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static inline void __b44_cam_write(struct b44 *bp, unsigned char *data, int index)
{
	u32 val;

	val  = ((u32) data[2]) << 24;
	val |= ((u32) data[3]) << 16;
	val |= ((u32) data[4]) <<  8;
	val |= ((u32) data[5]) <<  0;
	bw32(bp, B44_CAM_DATA_LO, val);
	val = (CAM_DATA_HI_VALID |
	       (((u32) data[0]) << 8) |
	       (((u32) data[1]) << 0));
	bw32(bp, B44_CAM_DATA_HI, val);
	bw32(bp, B44_CAM_CTRL, (CAM_CTRL_WRITE |
			    (index << CAM_CTRL_INDEX_SHIFT)));
	b44_wait_bit(bp, B44_CAM_CTRL, CAM_CTRL_BUSY, 100, 1);
}