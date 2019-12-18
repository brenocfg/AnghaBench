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

/* Variables and functions */
 int /*<<< orphan*/  b43legacy_is_cck_rate (int) ; 

__attribute__((used)) static inline
int b43legacy_is_ofdm_rate(int rate)
{
	return !b43legacy_is_cck_rate(rate);
}