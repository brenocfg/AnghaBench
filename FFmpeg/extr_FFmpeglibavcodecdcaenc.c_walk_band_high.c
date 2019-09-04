#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  (* walk_band_t ) (TYPE_1__*,int,int,int,int,int,int,int /*<<< orphan*/ *) ;
typedef  int /*<<< orphan*/  int32_t ;
struct TYPE_5__ {int* band_spectrum; } ;
typedef  TYPE_1__ DCAEncContext ;

/* Variables and functions */

__attribute__((used)) static void walk_band_high(DCAEncContext *c, int band, int channel,
                           walk_band_t walk, int32_t *arg)
{
    int f;

    if (band == 31) {
        for (f = 0; f < 4; f++)
            walk(c, 31, 31, 256 - 4 + f, 0, -2047, channel, arg);
    } else {
        for (f = 0; f < 8; f++)
            walk(c, band, band + 1, 8 * band + 4 + f,
                    c->band_spectrum[f], c->band_spectrum[7 - f], channel, arg);
    }
}