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
typedef  scalar_t__ uint64_t ;
struct AVBPrint {int dummy; } ;
struct TYPE_3__ {int nb_channels; scalar_t__ layout; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int FF_ARRAY_ELEMS (TYPE_1__*) ; 
 int UINT64_C (int) ; 
 int /*<<< orphan*/  av_bprintf (struct AVBPrint*,char*,...) ; 
 int av_get_channel_layout_nb_channels (scalar_t__) ; 
 TYPE_1__* channel_layout_map ; 
 char* get_channel_name (int) ; 

void av_bprint_channel_layout(struct AVBPrint *bp,
                              int nb_channels, uint64_t channel_layout)
{
    int i;

    if (nb_channels <= 0)
        nb_channels = av_get_channel_layout_nb_channels(channel_layout);

    for (i = 0; i < FF_ARRAY_ELEMS(channel_layout_map); i++)
        if (nb_channels    == channel_layout_map[i].nb_channels &&
            channel_layout == channel_layout_map[i].layout) {
            av_bprintf(bp, "%s", channel_layout_map[i].name);
            return;
        }

    av_bprintf(bp, "%d channels", nb_channels);
    if (channel_layout) {
        int i, ch;
        av_bprintf(bp, " (");
        for (i = 0, ch = 0; i < 64; i++) {
            if ((channel_layout & (UINT64_C(1) << i))) {
                const char *name = get_channel_name(i);
                if (name) {
                    if (ch > 0)
                        av_bprintf(bp, "+");
                    av_bprintf(bp, "%s", name);
                }
                ch++;
            }
        }
        av_bprintf(bp, ")");
    }
}