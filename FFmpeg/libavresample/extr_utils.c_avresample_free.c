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
typedef  int /*<<< orphan*/  AVAudioResampleContext ;

/* Variables and functions */
 int /*<<< orphan*/  av_freep (int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  av_opt_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  avresample_close (int /*<<< orphan*/ *) ; 

void avresample_free(AVAudioResampleContext **avr)
{
    if (!*avr)
        return;
    avresample_close(*avr);
    av_opt_free(*avr);
    av_freep(avr);
}