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
typedef  int /*<<< orphan*/  UINT8 ;

/* Variables and functions */
 int /*<<< orphan*/  btm_read_remote_features_complete (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void btu_hcif_read_rmt_features_comp_evt (UINT8 *p)
{
    btm_read_remote_features_complete(p);
}