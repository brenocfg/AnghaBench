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
struct media_bay_info {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  KEYLARGO_FCR1 ; 
 int /*<<< orphan*/  KL1_EIDE0_RESET_N ; 
 int /*<<< orphan*/  MB_BIS (struct media_bay_info*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void keylargo_mb_un_reset_ide(struct media_bay_info* bay)
{
	MB_BIS(bay, KEYLARGO_FCR1, KL1_EIDE0_RESET_N);
}