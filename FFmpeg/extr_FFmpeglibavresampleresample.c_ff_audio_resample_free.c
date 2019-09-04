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
struct TYPE_4__ {int /*<<< orphan*/  filter_bank; int /*<<< orphan*/  buffer; } ;
typedef  TYPE_1__ ResampleContext ;

/* Variables and functions */
 int /*<<< orphan*/  av_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  av_freep (TYPE_1__**) ; 
 int /*<<< orphan*/  ff_audio_data_free (int /*<<< orphan*/ *) ; 

void ff_audio_resample_free(ResampleContext **c)
{
    if (!*c)
        return;
    ff_audio_data_free(&(*c)->buffer);
    av_free((*c)->filter_bank);
    av_freep(c);
}