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
struct snd_korg1212 {int clkSource; int /*<<< orphan*/  clkRate; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  snd_korg1212_SetRate (struct snd_korg1212*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int snd_korg1212_SetClockSource(struct snd_korg1212 *korg1212, int source)
{

	if (source < 0 || source > 2)
		return -EINVAL;

        korg1212->clkSource = source;

        snd_korg1212_SetRate(korg1212, korg1212->clkRate);

        return 0;
}