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
typedef  int u64 ;
struct niu {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  TCAM_CTL ; 
 int TCAM_CTL_RWC_TCAM_WRITE ; 
 int /*<<< orphan*/  TCAM_CTL_STAT ; 
 int /*<<< orphan*/  TCAM_KEY_0 ; 
 int /*<<< orphan*/  TCAM_KEY_1 ; 
 int /*<<< orphan*/  TCAM_KEY_2 ; 
 int /*<<< orphan*/  TCAM_KEY_3 ; 
 int /*<<< orphan*/  TCAM_KEY_MASK_0 ; 
 int /*<<< orphan*/  TCAM_KEY_MASK_1 ; 
 int /*<<< orphan*/  TCAM_KEY_MASK_2 ; 
 int /*<<< orphan*/  TCAM_KEY_MASK_3 ; 
 int /*<<< orphan*/  nw64 (int /*<<< orphan*/ ,int) ; 
 int tcam_wait_bit (struct niu*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int tcam_write(struct niu *np, int index,
		      u64 *key, u64 *mask)
{
	nw64(TCAM_KEY_0, key[0]);
	nw64(TCAM_KEY_1, key[1]);
	nw64(TCAM_KEY_2, key[2]);
	nw64(TCAM_KEY_3, key[3]);
	nw64(TCAM_KEY_MASK_0, mask[0]);
	nw64(TCAM_KEY_MASK_1, mask[1]);
	nw64(TCAM_KEY_MASK_2, mask[2]);
	nw64(TCAM_KEY_MASK_3, mask[3]);
	nw64(TCAM_CTL, (TCAM_CTL_RWC_TCAM_WRITE | index));

	return tcam_wait_bit(np, TCAM_CTL_STAT);
}