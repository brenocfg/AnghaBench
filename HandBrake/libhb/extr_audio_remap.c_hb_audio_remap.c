#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_3__ {int /*<<< orphan*/  table; int /*<<< orphan*/  nchannels; int /*<<< orphan*/  (* remap ) (int /*<<< orphan*/ **,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;scalar_t__ remap_needed; } ;
typedef  TYPE_1__ hb_audio_remap_t ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ **,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void hb_audio_remap(hb_audio_remap_t *remap, uint8_t **samples, int nsamples)
{
    if (remap != NULL && remap->remap_needed)
    {
        remap->remap(samples, nsamples, remap->nchannels, remap->table);
    }
}