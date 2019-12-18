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
struct zd_mc_hash {int dummy; } ;
struct zd_mac {int /*<<< orphan*/  chip; } ;

/* Variables and functions */
 int zd_chip_set_multicast_hash (int /*<<< orphan*/ *,struct zd_mc_hash*) ; 
 int /*<<< orphan*/  zd_mc_clear (struct zd_mc_hash*) ; 

__attribute__((used)) static int set_mc_hash(struct zd_mac *mac)
{
	struct zd_mc_hash hash;
	zd_mc_clear(&hash);
	return zd_chip_set_multicast_hash(&mac->chip, &hash);
}