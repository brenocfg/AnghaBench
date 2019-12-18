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
struct geom {int chunk_mask; int chunk_shift; int near_copies; int far_copies; int /*<<< orphan*/  raid_disks; } ;
typedef  int sector_t ;

/* Variables and functions */
 int DIV_ROUND_UP_SECTOR_T (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static sector_t last_dev_address(sector_t s, struct geom *geo)
{
	s = (s | geo->chunk_mask) + 1;
	s >>= geo->chunk_shift;
	s *= geo->near_copies;
	s = DIV_ROUND_UP_SECTOR_T(s, geo->raid_disks);
	s *= geo->far_copies;
	s <<= geo->chunk_shift;
	return s;
}