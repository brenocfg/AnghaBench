#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  dc; } ;
typedef  TYPE_1__ AudioConvert ;

/* Variables and functions */
 int /*<<< orphan*/  av_freep (TYPE_1__**) ; 
 int /*<<< orphan*/  ff_dither_free (int /*<<< orphan*/ *) ; 

void ff_audio_convert_free(AudioConvert **ac)
{
    if (!*ac)
        return;
    ff_dither_free(&(*ac)->dc);
    av_freep(ac);
}