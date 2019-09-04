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
struct TYPE_5__ {int bps; int /*<<< orphan*/  gb; scalar_t__** temp16; TYPE_1__* vlc; scalar_t__** temp; } ;
struct TYPE_4__ {int /*<<< orphan*/  table; } ;
typedef  TYPE_2__ HYuvContext ;

/* Variables and functions */
 scalar_t__ BITS_LEFT (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  CLOSE_READER (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  OP14bits ; 
 int /*<<< orphan*/  OP8bits ; 
 int /*<<< orphan*/  OPEN_READER (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  READ_2PIX_PLANE (scalar_t__,scalar_t__,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  READ_2PIX_PLANE16 (scalar_t__,scalar_t__,int) ; 
 unsigned int SHOW_UBITS (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UPDATE_CACHE (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  VLC_BITS ; 
 int /*<<< orphan*/  VLC_INTERN (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 scalar_t__ get_bits (int /*<<< orphan*/ *,int) ; 
 int get_bits_left (int /*<<< orphan*/ *) ; 
 int get_vlc2 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  re ; 

__attribute__((used)) static void decode_plane_bitstream(HYuvContext *s, int width, int plane)
{
    int i, count = width/2;

    if (s->bps <= 8) {
        OPEN_READER(re, &s->gb);
        if (count >= (get_bits_left(&s->gb)) / (32 * 2)) {
            for (i = 0; i < count && BITS_LEFT(re, &s->gb) > 0; i++) {
                READ_2PIX_PLANE(s->temp[0][2 * i], s->temp[0][2 * i + 1], plane, OP8bits);
            }
        } else {
            for(i=0; i<count; i++){
                READ_2PIX_PLANE(s->temp[0][2 * i], s->temp[0][2 * i + 1], plane, OP8bits);
            }
        }
        if( width&1 && BITS_LEFT(re, &s->gb)>0 ) {
            unsigned int index;
            int nb_bits, code, n;
            UPDATE_CACHE(re, &s->gb);
            index = SHOW_UBITS(re, &s->gb, VLC_BITS);
            VLC_INTERN(s->temp[0][width-1], s->vlc[plane].table,
                       &s->gb, re, VLC_BITS, 3);
        }
        CLOSE_READER(re, &s->gb);
    } else if (s->bps <= 14) {
        OPEN_READER(re, &s->gb);
        if (count >= (get_bits_left(&s->gb)) / (32 * 2)) {
            for (i = 0; i < count && BITS_LEFT(re, &s->gb) > 0; i++) {
                READ_2PIX_PLANE(s->temp16[0][2 * i], s->temp16[0][2 * i + 1], plane, OP14bits);
            }
        } else {
            for(i=0; i<count; i++){
                READ_2PIX_PLANE(s->temp16[0][2 * i], s->temp16[0][2 * i + 1], plane, OP14bits);
            }
        }
        if( width&1 && BITS_LEFT(re, &s->gb)>0 ) {
            unsigned int index;
            int nb_bits, code, n;
            UPDATE_CACHE(re, &s->gb);
            index = SHOW_UBITS(re, &s->gb, VLC_BITS);
            VLC_INTERN(s->temp16[0][width-1], s->vlc[plane].table,
                       &s->gb, re, VLC_BITS, 3);
        }
        CLOSE_READER(re, &s->gb);
    } else {
        if (count >= (get_bits_left(&s->gb)) / (32 * 2)) {
            for (i = 0; i < count && get_bits_left(&s->gb) > 0; i++) {
                READ_2PIX_PLANE16(s->temp16[0][2 * i], s->temp16[0][2 * i + 1], plane);
            }
        } else {
            for(i=0; i<count; i++){
                READ_2PIX_PLANE16(s->temp16[0][2 * i], s->temp16[0][2 * i + 1], plane);
            }
        }
        if( width&1 && get_bits_left(&s->gb)>0 ) {
            int dst = get_vlc2(&s->gb, s->vlc[plane].table, VLC_BITS, 3)<<2;
            s->temp16[0][width-1] = dst + get_bits(&s->gb, 2);
        }
    }
}