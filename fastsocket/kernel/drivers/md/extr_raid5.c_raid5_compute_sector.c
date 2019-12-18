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
struct stripe_head {int pd_idx; int qd_idx; int ddf_layout; } ;
struct r5conf {int prev_algo; int algorithm; int prev_chunk_sectors; int chunk_sectors; int previous_raid_disks; int raid_disks; int max_degraded; int level; } ;
typedef  int sector_t ;

/* Variables and functions */
#define  ALGORITHM_LEFT_ASYMMETRIC 141 
#define  ALGORITHM_LEFT_ASYMMETRIC_6 140 
#define  ALGORITHM_LEFT_SYMMETRIC 139 
#define  ALGORITHM_LEFT_SYMMETRIC_6 138 
#define  ALGORITHM_PARITY_0 137 
#define  ALGORITHM_PARITY_0_6 136 
#define  ALGORITHM_PARITY_N 135 
#define  ALGORITHM_RIGHT_ASYMMETRIC 134 
#define  ALGORITHM_RIGHT_ASYMMETRIC_6 133 
#define  ALGORITHM_RIGHT_SYMMETRIC 132 
#define  ALGORITHM_RIGHT_SYMMETRIC_6 131 
#define  ALGORITHM_ROTATING_N_CONTINUE 130 
#define  ALGORITHM_ROTATING_N_RESTART 129 
#define  ALGORITHM_ROTATING_ZERO_RESTART 128 
 int /*<<< orphan*/  BUG () ; 
 int sector_div (int,int) ; 

__attribute__((used)) static sector_t raid5_compute_sector(struct r5conf *conf, sector_t r_sector,
				     int previous, int *dd_idx,
				     struct stripe_head *sh)
{
	sector_t stripe, stripe2;
	sector_t chunk_number;
	unsigned int chunk_offset;
	int pd_idx, qd_idx;
	int ddf_layout = 0;
	sector_t new_sector;
	int algorithm = previous ? conf->prev_algo
				 : conf->algorithm;
	int sectors_per_chunk = previous ? conf->prev_chunk_sectors
					 : conf->chunk_sectors;
	int raid_disks = previous ? conf->previous_raid_disks
				  : conf->raid_disks;
	int data_disks = raid_disks - conf->max_degraded;

	/* First compute the information on this sector */

	/*
	 * Compute the chunk number and the sector offset inside the chunk
	 */
	chunk_offset = sector_div(r_sector, sectors_per_chunk);
	chunk_number = r_sector;

	/*
	 * Compute the stripe number
	 */
	stripe = chunk_number;
	*dd_idx = sector_div(stripe, data_disks);
	stripe2 = stripe;
	/*
	 * Select the parity disk based on the user selected algorithm.
	 */
	pd_idx = qd_idx = -1;
	switch(conf->level) {
	case 4:
		pd_idx = data_disks;
		break;
	case 5:
		switch (algorithm) {
		case ALGORITHM_LEFT_ASYMMETRIC:
			pd_idx = data_disks - sector_div(stripe2, raid_disks);
			if (*dd_idx >= pd_idx)
				(*dd_idx)++;
			break;
		case ALGORITHM_RIGHT_ASYMMETRIC:
			pd_idx = sector_div(stripe2, raid_disks);
			if (*dd_idx >= pd_idx)
				(*dd_idx)++;
			break;
		case ALGORITHM_LEFT_SYMMETRIC:
			pd_idx = data_disks - sector_div(stripe2, raid_disks);
			*dd_idx = (pd_idx + 1 + *dd_idx) % raid_disks;
			break;
		case ALGORITHM_RIGHT_SYMMETRIC:
			pd_idx = sector_div(stripe2, raid_disks);
			*dd_idx = (pd_idx + 1 + *dd_idx) % raid_disks;
			break;
		case ALGORITHM_PARITY_0:
			pd_idx = 0;
			(*dd_idx)++;
			break;
		case ALGORITHM_PARITY_N:
			pd_idx = data_disks;
			break;
		default:
			BUG();
		}
		break;
	case 6:

		switch (algorithm) {
		case ALGORITHM_LEFT_ASYMMETRIC:
			pd_idx = raid_disks - 1 - sector_div(stripe2, raid_disks);
			qd_idx = pd_idx + 1;
			if (pd_idx == raid_disks-1) {
				(*dd_idx)++;	/* Q D D D P */
				qd_idx = 0;
			} else if (*dd_idx >= pd_idx)
				(*dd_idx) += 2; /* D D P Q D */
			break;
		case ALGORITHM_RIGHT_ASYMMETRIC:
			pd_idx = sector_div(stripe2, raid_disks);
			qd_idx = pd_idx + 1;
			if (pd_idx == raid_disks-1) {
				(*dd_idx)++;	/* Q D D D P */
				qd_idx = 0;
			} else if (*dd_idx >= pd_idx)
				(*dd_idx) += 2; /* D D P Q D */
			break;
		case ALGORITHM_LEFT_SYMMETRIC:
			pd_idx = raid_disks - 1 - sector_div(stripe2, raid_disks);
			qd_idx = (pd_idx + 1) % raid_disks;
			*dd_idx = (pd_idx + 2 + *dd_idx) % raid_disks;
			break;
		case ALGORITHM_RIGHT_SYMMETRIC:
			pd_idx = sector_div(stripe2, raid_disks);
			qd_idx = (pd_idx + 1) % raid_disks;
			*dd_idx = (pd_idx + 2 + *dd_idx) % raid_disks;
			break;

		case ALGORITHM_PARITY_0:
			pd_idx = 0;
			qd_idx = 1;
			(*dd_idx) += 2;
			break;
		case ALGORITHM_PARITY_N:
			pd_idx = data_disks;
			qd_idx = data_disks + 1;
			break;

		case ALGORITHM_ROTATING_ZERO_RESTART:
			/* Exactly the same as RIGHT_ASYMMETRIC, but or
			 * of blocks for computing Q is different.
			 */
			pd_idx = sector_div(stripe2, raid_disks);
			qd_idx = pd_idx + 1;
			if (pd_idx == raid_disks-1) {
				(*dd_idx)++;	/* Q D D D P */
				qd_idx = 0;
			} else if (*dd_idx >= pd_idx)
				(*dd_idx) += 2; /* D D P Q D */
			ddf_layout = 1;
			break;

		case ALGORITHM_ROTATING_N_RESTART:
			/* Same a left_asymmetric, by first stripe is
			 * D D D P Q  rather than
			 * Q D D D P
			 */
			stripe2 += 1;
			pd_idx = raid_disks - 1 - sector_div(stripe2, raid_disks);
			qd_idx = pd_idx + 1;
			if (pd_idx == raid_disks-1) {
				(*dd_idx)++;	/* Q D D D P */
				qd_idx = 0;
			} else if (*dd_idx >= pd_idx)
				(*dd_idx) += 2; /* D D P Q D */
			ddf_layout = 1;
			break;

		case ALGORITHM_ROTATING_N_CONTINUE:
			/* Same as left_symmetric but Q is before P */
			pd_idx = raid_disks - 1 - sector_div(stripe2, raid_disks);
			qd_idx = (pd_idx + raid_disks - 1) % raid_disks;
			*dd_idx = (pd_idx + 1 + *dd_idx) % raid_disks;
			ddf_layout = 1;
			break;

		case ALGORITHM_LEFT_ASYMMETRIC_6:
			/* RAID5 left_asymmetric, with Q on last device */
			pd_idx = data_disks - sector_div(stripe2, raid_disks-1);
			if (*dd_idx >= pd_idx)
				(*dd_idx)++;
			qd_idx = raid_disks - 1;
			break;

		case ALGORITHM_RIGHT_ASYMMETRIC_6:
			pd_idx = sector_div(stripe2, raid_disks-1);
			if (*dd_idx >= pd_idx)
				(*dd_idx)++;
			qd_idx = raid_disks - 1;
			break;

		case ALGORITHM_LEFT_SYMMETRIC_6:
			pd_idx = data_disks - sector_div(stripe2, raid_disks-1);
			*dd_idx = (pd_idx + 1 + *dd_idx) % (raid_disks-1);
			qd_idx = raid_disks - 1;
			break;

		case ALGORITHM_RIGHT_SYMMETRIC_6:
			pd_idx = sector_div(stripe2, raid_disks-1);
			*dd_idx = (pd_idx + 1 + *dd_idx) % (raid_disks-1);
			qd_idx = raid_disks - 1;
			break;

		case ALGORITHM_PARITY_0_6:
			pd_idx = 0;
			(*dd_idx)++;
			qd_idx = raid_disks - 1;
			break;

		default:
			BUG();
		}
		break;
	}

	if (sh) {
		sh->pd_idx = pd_idx;
		sh->qd_idx = qd_idx;
		sh->ddf_layout = ddf_layout;
	}
	/*
	 * Finally, compute the new sector number
	 */
	new_sector = (sector_t)stripe * sectors_per_chunk + chunk_offset;
	return new_sector;
}