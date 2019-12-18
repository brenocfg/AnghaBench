#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_11__ {scalar_t__ hd_stream_id; int xll_offset; int /*<<< orphan*/  xll_size; } ;
struct TYPE_10__ {scalar_t__ hd_stream_id; scalar_t__ pbr_length; } ;
typedef  TYPE_1__ DCAXllDecoder ;
typedef  TYPE_2__ DCAExssAsset ;

/* Variables and functions */
 int /*<<< orphan*/  clear_pbr (TYPE_1__*) ; 
 int parse_frame_no_pbr (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_2__*) ; 
 int parse_frame_pbr (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_2__*) ; 

int ff_dca_xll_parse(DCAXllDecoder *s, uint8_t *data, DCAExssAsset *asset)
{
    int ret;

    if (s->hd_stream_id != asset->hd_stream_id) {
        clear_pbr(s);
        s->hd_stream_id = asset->hd_stream_id;
    }

    if (s->pbr_length)
        ret = parse_frame_pbr(s, data + asset->xll_offset, asset->xll_size, asset);
    else
        ret = parse_frame_no_pbr(s, data + asset->xll_offset, asset->xll_size, asset);

    return ret;
}