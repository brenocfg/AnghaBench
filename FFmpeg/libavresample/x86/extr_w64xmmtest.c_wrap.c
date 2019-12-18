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
typedef  int /*<<< orphan*/  wrap ;
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  AVAudioResampleContext ;

/* Variables and functions */
 int /*<<< orphan*/  testxmmclobbers (int /*<<< orphan*/  (*) (int /*<<< orphan*/ *,int /*<<< orphan*/ **,int,int,int /*<<< orphan*/ **,int,int),int /*<<< orphan*/ *,int /*<<< orphan*/ **,int,int,int /*<<< orphan*/ **,int,int) ; 

wrap(avresample_convert(AVAudioResampleContext *avr, uint8_t **output,
                        int out_plane_size, int out_samples, uint8_t **input,
                        int in_plane_size, int in_samples))
{
    testxmmclobbers(avresample_convert, avr, output, out_plane_size,
                    out_samples, input, in_plane_size, in_samples);
}