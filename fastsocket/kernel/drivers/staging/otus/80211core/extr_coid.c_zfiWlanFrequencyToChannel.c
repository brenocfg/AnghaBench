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
typedef  int /*<<< orphan*/  zdev_t ;
typedef  int /*<<< orphan*/  u8_t ;
typedef  int /*<<< orphan*/  u16_t ;

/* Variables and functions */
 int /*<<< orphan*/  zfChFreqToNum (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

u8_t zfiWlanFrequencyToChannel(zdev_t* dev, u16_t freq)
{
    u8_t is5GBand = 0;

    return zfChFreqToNum(freq, &is5GBand);
}