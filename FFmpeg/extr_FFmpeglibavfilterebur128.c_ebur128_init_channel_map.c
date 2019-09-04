#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int channels; TYPE_1__* d; } ;
struct TYPE_4__ {int* channel_map; } ;
typedef  TYPE_2__ FFEBUR128State ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ENOMEM ; 
 void* FF_EBUR128_CENTER ; 
 void* FF_EBUR128_LEFT ; 
 void* FF_EBUR128_LEFT_SURROUND ; 
 void* FF_EBUR128_RIGHT ; 
 void* FF_EBUR128_RIGHT_SURROUND ; 
 void* FF_EBUR128_UNUSED ; 
 scalar_t__ av_malloc_array (int,int) ; 

__attribute__((used)) static int ebur128_init_channel_map(FFEBUR128State * st)
{
    size_t i;
    st->d->channel_map =
        (int *) av_malloc_array(st->channels, sizeof(int));
    if (!st->d->channel_map)
        return AVERROR(ENOMEM);
    if (st->channels == 4) {
        st->d->channel_map[0] = FF_EBUR128_LEFT;
        st->d->channel_map[1] = FF_EBUR128_RIGHT;
        st->d->channel_map[2] = FF_EBUR128_LEFT_SURROUND;
        st->d->channel_map[3] = FF_EBUR128_RIGHT_SURROUND;
    } else if (st->channels == 5) {
        st->d->channel_map[0] = FF_EBUR128_LEFT;
        st->d->channel_map[1] = FF_EBUR128_RIGHT;
        st->d->channel_map[2] = FF_EBUR128_CENTER;
        st->d->channel_map[3] = FF_EBUR128_LEFT_SURROUND;
        st->d->channel_map[4] = FF_EBUR128_RIGHT_SURROUND;
    } else {
        for (i = 0; i < st->channels; ++i) {
            switch (i) {
            case 0:
                st->d->channel_map[i] = FF_EBUR128_LEFT;
                break;
            case 1:
                st->d->channel_map[i] = FF_EBUR128_RIGHT;
                break;
            case 2:
                st->d->channel_map[i] = FF_EBUR128_CENTER;
                break;
            case 3:
                st->d->channel_map[i] = FF_EBUR128_UNUSED;
                break;
            case 4:
                st->d->channel_map[i] = FF_EBUR128_LEFT_SURROUND;
                break;
            case 5:
                st->d->channel_map[i] = FF_EBUR128_RIGHT_SURROUND;
                break;
            default:
                st->d->channel_map[i] = FF_EBUR128_UNUSED;
                break;
            }
        }
    }
    return 0;
}