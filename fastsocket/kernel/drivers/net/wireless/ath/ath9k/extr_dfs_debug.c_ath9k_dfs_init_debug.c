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
struct TYPE_2__ {int /*<<< orphan*/  debugfs_phy; } ;
struct ath_softc {TYPE_1__ debug; } ;

/* Variables and functions */
 int /*<<< orphan*/  S_IRUSR ; 
 int /*<<< orphan*/  S_IWUSR ; 
 int /*<<< orphan*/  debugfs_create_file (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct ath_softc*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fops_dfs_stats ; 
 int /*<<< orphan*/  fops_simulate_radar ; 

void ath9k_dfs_init_debug(struct ath_softc *sc)
{
	debugfs_create_file("dfs_stats", S_IRUSR,
			    sc->debug.debugfs_phy, sc, &fops_dfs_stats);
	debugfs_create_file("dfs_simulate_radar", S_IWUSR,
			    sc->debug.debugfs_phy, sc, &fops_simulate_radar);
}