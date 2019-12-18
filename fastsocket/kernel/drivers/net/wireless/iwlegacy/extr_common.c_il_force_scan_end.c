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
struct il_priv {int /*<<< orphan*/  status; int /*<<< orphan*/  mutex; } ;

/* Variables and functions */
 int /*<<< orphan*/  D_SCAN (char*) ; 
 int /*<<< orphan*/  S_SCANNING ; 
 int /*<<< orphan*/  S_SCAN_ABORTING ; 
 int /*<<< orphan*/  S_SCAN_HW ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  il_complete_scan (struct il_priv*,int) ; 
 int /*<<< orphan*/  lockdep_assert_held (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void
il_force_scan_end(struct il_priv *il)
{
	lockdep_assert_held(&il->mutex);

	if (!test_bit(S_SCANNING, &il->status)) {
		D_SCAN("Forcing scan end while not scanning\n");
		return;
	}

	D_SCAN("Forcing scan end\n");
	clear_bit(S_SCANNING, &il->status);
	clear_bit(S_SCAN_HW, &il->status);
	clear_bit(S_SCAN_ABORTING, &il->status);
	il_complete_scan(il, true);
}