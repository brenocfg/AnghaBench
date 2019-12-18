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
struct gemtek {unsigned long lastfreq; scalar_t__ muted; } ;

/* Variables and functions */
 int /*<<< orphan*/  BU2614_FMES ; 
 int /*<<< orphan*/  BU2614_FMUN ; 
 int /*<<< orphan*/  BU2614_FREQ ; 
 int /*<<< orphan*/  BU2614_PORT ; 
 int /*<<< orphan*/  BU2614_STDF ; 
 int /*<<< orphan*/  BU2614_SWAL ; 
 int /*<<< orphan*/  BU2614_SWIN ; 
 int /*<<< orphan*/  BU2614_TEST ; 
 int /*<<< orphan*/  GEMTEK_HIGHFREQ ; 
 int /*<<< orphan*/  GEMTEK_LOWFREQ ; 
 int GEMTEK_STDF_3_125_KHZ ; 
 unsigned long clamp_val (unsigned long,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gemtek_bu2614_set (struct gemtek*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  gemtek_bu2614_transmit (struct gemtek*) ; 
 int gemtek_convfreq (unsigned long) ; 
 scalar_t__ hardmute ; 
 scalar_t__ keepmuted ; 

__attribute__((used)) static void gemtek_setfreq(struct gemtek *gt, unsigned long freq)
{
	if (keepmuted && hardmute && gt->muted)
		return;

	freq = clamp_val(freq, GEMTEK_LOWFREQ, GEMTEK_HIGHFREQ);

	gt->lastfreq = freq;
	gt->muted = 0;

	gemtek_bu2614_set(gt, BU2614_PORT, 0);
	gemtek_bu2614_set(gt, BU2614_FMES, 0);
	gemtek_bu2614_set(gt, BU2614_SWIN, 0);	/* FM-mode	*/
	gemtek_bu2614_set(gt, BU2614_SWAL, 0);
	gemtek_bu2614_set(gt, BU2614_FMUN, 1);	/* GT bit set	*/
	gemtek_bu2614_set(gt, BU2614_TEST, 0);

	gemtek_bu2614_set(gt, BU2614_STDF, GEMTEK_STDF_3_125_KHZ);
	gemtek_bu2614_set(gt, BU2614_FREQ, gemtek_convfreq(freq));

	gemtek_bu2614_transmit(gt);
}