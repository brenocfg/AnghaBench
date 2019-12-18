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
struct zd_mc_hash {int /*<<< orphan*/  high; int /*<<< orphan*/  low; } ;
struct zd_ioreq32 {int /*<<< orphan*/  member_1; int /*<<< orphan*/  member_0; } ;
struct zd_chip {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (struct zd_ioreq32 const*) ; 
 int /*<<< orphan*/  CR_GROUP_HASH_P1 ; 
 int /*<<< orphan*/  CR_GROUP_HASH_P2 ; 
 int zd_iowrite32a (struct zd_chip*,struct zd_ioreq32 const*,int /*<<< orphan*/ ) ; 

int zd_chip_set_multicast_hash(struct zd_chip *chip,
	                       struct zd_mc_hash *hash)
{
	const struct zd_ioreq32 ioreqs[] = {
		{ CR_GROUP_HASH_P1, hash->low },
		{ CR_GROUP_HASH_P2, hash->high },
	};

	return zd_iowrite32a(chip, ioreqs, ARRAY_SIZE(ioreqs));
}