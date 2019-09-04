#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int numXtiles; int numYtiles; int /*<<< orphan*/  g; TYPE_2__* tile; } ;
struct TYPE_9__ {TYPE_1__* tile_part; } ;
struct TYPE_8__ {int /*<<< orphan*/  tpg; } ;
typedef  TYPE_2__ Jpeg2000Tile ;
typedef  TYPE_3__ Jpeg2000DecoderContext ;

/* Variables and functions */
 int init_tile (TYPE_3__*,int) ; 
 int jpeg2000_decode_packets (TYPE_3__*,TYPE_2__*) ; 

__attribute__((used)) static int jpeg2000_read_bitstream_packets(Jpeg2000DecoderContext *s)
{
    int ret = 0;
    int tileno;

    for (tileno = 0; tileno < s->numXtiles * s->numYtiles; tileno++) {
        Jpeg2000Tile *tile = s->tile + tileno;

        if ((ret = init_tile(s, tileno)) < 0)
            return ret;

        s->g = tile->tile_part[0].tpg;
        if ((ret = jpeg2000_decode_packets(s, tile)) < 0)
            return ret;
    }

    return 0;
}