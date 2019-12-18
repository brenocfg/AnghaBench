#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  sample_aspect_ratio; int /*<<< orphan*/  height; int /*<<< orphan*/  width; int /*<<< orphan*/  channel_layout; int /*<<< orphan*/  channels; int /*<<< orphan*/  sample_rate; int /*<<< orphan*/  format; } ;
struct TYPE_5__ {int /*<<< orphan*/  sample_aspect_ratio; int /*<<< orphan*/  height; int /*<<< orphan*/  width; int /*<<< orphan*/  channel_layout; int /*<<< orphan*/  channels; int /*<<< orphan*/  sample_rate; int /*<<< orphan*/  format; } ;
typedef  TYPE_1__ InputFilter ;
typedef  TYPE_2__ AVCodecParameters ;

/* Variables and functions */

__attribute__((used)) static void ifilter_parameters_from_codecpar(InputFilter *ifilter, AVCodecParameters *par)
{
    // We never got any input. Set a fake format, which will
    // come from libavformat.
    ifilter->format                 = par->format;
    ifilter->sample_rate            = par->sample_rate;
    ifilter->channels               = par->channels;
    ifilter->channel_layout         = par->channel_layout;
    ifilter->width                  = par->width;
    ifilter->height                 = par->height;
    ifilter->sample_aspect_ratio    = par->sample_aspect_ratio;
}