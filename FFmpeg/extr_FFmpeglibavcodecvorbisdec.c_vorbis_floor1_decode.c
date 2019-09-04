#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_8__ ;
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {int multiplier; unsigned int partitions; unsigned int* partition_class; unsigned int* class_dimensions; unsigned int* class_subclasses; size_t* class_masterbook; int** subclass_books; unsigned int x_list_dim; TYPE_8__* list; } ;
struct TYPE_11__ {TYPE_4__ t1; } ;
typedef  TYPE_3__ vorbis_floor_data ;
typedef  TYPE_4__ vorbis_floor1 ;
struct TYPE_13__ {TYPE_2__* codebooks; int /*<<< orphan*/  gb; } ;
typedef  TYPE_5__ vorbis_context ;
typedef  int uint16_t ;
struct TYPE_14__ {int x; unsigned int low; unsigned int high; } ;
struct TYPE_9__ {int /*<<< orphan*/  table; } ;
struct TYPE_10__ {int /*<<< orphan*/  nb_bits; TYPE_1__ vlc; } ;
typedef  int /*<<< orphan*/  GetBitContext ;

/* Variables and functions */
 int AVERROR_INVALIDDATA ; 
 int FFABS (int) ; 
 int av_clip_uint16 (int) ; 
 int /*<<< orphan*/  ff_dlog (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  ff_vorbis_floor1_render_list (TYPE_8__*,unsigned int,int*,int*,int,float*,int) ; 
 int get_bits (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_bits1 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  get_bits_count (int /*<<< orphan*/ *) ; 
 void* get_vlc2 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ilog (unsigned int) ; 

__attribute__((used)) static int vorbis_floor1_decode(vorbis_context *vc,
                                vorbis_floor_data *vfu, float *vec)
{
    vorbis_floor1 *vf = &vfu->t1;
    GetBitContext *gb = &vc->gb;
    uint16_t range_v[4] = { 256, 128, 86, 64 };
    unsigned range = range_v[vf->multiplier - 1];
    uint16_t floor1_Y[258];
    uint16_t floor1_Y_final[258];
    int floor1_flag[258];
    unsigned partition_class, cdim, cbits, csub, cval, offset, i, j;
    int book, adx, ady, dy, off, predicted, err;


    if (!get_bits1(gb)) // silence
        return 1;

// Read values (or differences) for the floor's points

    floor1_Y[0] = get_bits(gb, ilog(range - 1));
    floor1_Y[1] = get_bits(gb, ilog(range - 1));

    ff_dlog(NULL, "floor 0 Y %d floor 1 Y %d \n", floor1_Y[0], floor1_Y[1]);

    offset = 2;
    for (i = 0; i < vf->partitions; ++i) {
        partition_class = vf->partition_class[i];
        cdim   = vf->class_dimensions[partition_class];
        cbits  = vf->class_subclasses[partition_class];
        csub = (1 << cbits) - 1;
        cval = 0;

        ff_dlog(NULL, "Cbits %u\n", cbits);

        if (cbits) // this reads all subclasses for this partition's class
            cval = get_vlc2(gb, vc->codebooks[vf->class_masterbook[partition_class]].vlc.table,
                            vc->codebooks[vf->class_masterbook[partition_class]].nb_bits, 3);

        for (j = 0; j < cdim; ++j) {
            book = vf->subclass_books[partition_class][cval & csub];

            ff_dlog(NULL, "book %d Cbits %u cval %u  bits:%d\n",
                    book, cbits, cval, get_bits_count(gb));

            cval = cval >> cbits;
            if (book > -1) {
                int v = get_vlc2(gb, vc->codebooks[book].vlc.table,
                                 vc->codebooks[book].nb_bits, 3);
                if (v < 0)
                    return AVERROR_INVALIDDATA;
                floor1_Y[offset+j] = v;
            } else {
                floor1_Y[offset+j] = 0;
            }

            ff_dlog(NULL, " floor(%d) = %d \n",
                    vf->list[offset+j].x, floor1_Y[offset+j]);
        }
        offset+=cdim;
    }

// Amplitude calculation from the differences

    floor1_flag[0] = 1;
    floor1_flag[1] = 1;
    floor1_Y_final[0] = floor1_Y[0];
    floor1_Y_final[1] = floor1_Y[1];

    for (i = 2; i < vf->x_list_dim; ++i) {
        unsigned val, highroom, lowroom, room, high_neigh_offs, low_neigh_offs;

        low_neigh_offs  = vf->list[i].low;
        high_neigh_offs = vf->list[i].high;
        dy  = floor1_Y_final[high_neigh_offs] - floor1_Y_final[low_neigh_offs];  // render_point begin
        adx = vf->list[high_neigh_offs].x - vf->list[low_neigh_offs].x;
        ady = FFABS(dy);
        err = ady * (vf->list[i].x - vf->list[low_neigh_offs].x);
        off = err / adx;
        if (dy < 0) {
            predicted = floor1_Y_final[low_neigh_offs] - off;
        } else {
            predicted = floor1_Y_final[low_neigh_offs] + off;
        } // render_point end

        val = floor1_Y[i];
        highroom = range-predicted;
        lowroom  = predicted;
        if (highroom < lowroom) {
            room = highroom * 2;
        } else {
            room = lowroom * 2;   // SPEC misspelling
        }
        if (val) {
            floor1_flag[low_neigh_offs]  = 1;
            floor1_flag[high_neigh_offs] = 1;
            floor1_flag[i]               = 1;
            if (val >= room) {
                if (highroom > lowroom) {
                    floor1_Y_final[i] = av_clip_uint16(val - lowroom + predicted);
                } else {
                    floor1_Y_final[i] = av_clip_uint16(predicted - val + highroom - 1);
                }
            } else {
                if (val & 1) {
                    floor1_Y_final[i] = av_clip_uint16(predicted - (val + 1) / 2);
                } else {
                    floor1_Y_final[i] = av_clip_uint16(predicted + val / 2);
                }
            }
        } else {
            floor1_flag[i]    = 0;
            floor1_Y_final[i] = av_clip_uint16(predicted);
        }

        ff_dlog(NULL, " Decoded floor(%d) = %u / val %u\n",
                vf->list[i].x, floor1_Y_final[i], val);
    }

// Curve synth - connect the calculated dots and convert from dB scale FIXME optimize ?

    ff_vorbis_floor1_render_list(vf->list, vf->x_list_dim, floor1_Y_final, floor1_flag, vf->multiplier, vec, vf->list[1].x);

    ff_dlog(NULL, " Floor decoded\n");

    return 0;
}