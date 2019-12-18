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
struct TYPE_2__ {int ia_rows; } ;
struct ath_hw {TYPE_1__ iniPcieSerdesWow; } ;

/* Variables and functions */
 int /*<<< orphan*/  INI_RA (TYPE_1__*,int,int) ; 
 int /*<<< orphan*/  REG_WRITE (struct ath_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 

__attribute__((used)) static void ath9k_hw_config_serdes_wow_sleep(struct ath_hw *ah)
{
	int i;

	for (i = 0; i < ah->iniPcieSerdesWow.ia_rows; i++)
		REG_WRITE(ah, INI_RA(&ah->iniPcieSerdesWow, i, 0),
			  INI_RA(&ah->iniPcieSerdesWow, i, 1));

	usleep_range(1000, 1500);
}