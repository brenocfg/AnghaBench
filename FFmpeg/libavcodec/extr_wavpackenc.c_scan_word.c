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
typedef  scalar_t__ uint32_t ;
typedef  int /*<<< orphan*/  int32_t ;
typedef  int /*<<< orphan*/  WvChannel ;
typedef  int /*<<< orphan*/  WavPackEncodeContext ;

/* Variables and functions */
 int /*<<< orphan*/  DEC_MED (int) ; 
 scalar_t__ GET_MED (int) ; 
 int /*<<< orphan*/  INC_MED (int) ; 
 scalar_t__ labs (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void scan_word(WavPackEncodeContext *s, WvChannel *c,
                      int32_t *samples, int nb_samples, int dir)
{
    if (dir < 0)
        samples += nb_samples - 1;

    while (nb_samples--) {
        uint32_t low, value = labs(samples[0]);

        if (value < GET_MED(0)) {
            DEC_MED(0);
        } else {
            low = GET_MED(0);
            INC_MED(0);

            if (value - low < GET_MED(1)) {
                DEC_MED(1);
            } else {
                low += GET_MED(1);
                INC_MED(1);

                if (value - low < GET_MED(2)) {
                    DEC_MED(2);
                } else {
                    INC_MED(2);
                }
            }
        }
        samples += dir;
    }
}