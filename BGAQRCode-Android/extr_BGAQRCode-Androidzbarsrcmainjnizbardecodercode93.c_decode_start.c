#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  zbar_symbol_type_t ;
struct TYPE_8__ {unsigned int direction; int element; unsigned int width; scalar_t__ character; } ;
struct TYPE_7__ {unsigned int s6; TYPE_2__ code93; } ;
typedef  TYPE_1__ zbar_decoder_t ;
typedef  TYPE_2__ code93_decoder_t ;

/* Variables and functions */
 int /*<<< orphan*/  ZBAR_NONE ; 
 int /*<<< orphan*/  ZBAR_PARTIAL ; 
 int /*<<< orphan*/  dbprintf (int,char*,...) ; 
 scalar_t__ decode_e (int /*<<< orphan*/ ,unsigned int,int) ; 
 int encode6 (TYPE_1__*) ; 
 unsigned int get_width (TYPE_1__*,int) ; 
 int /*<<< orphan*/  pair_width (TYPE_1__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline zbar_symbol_type_t
decode_start (zbar_decoder_t *dcode)
{
    code93_decoder_t *dcode93 = &dcode->code93;
    unsigned dir, qz, s = dcode->s6;
    int c;

    dbprintf(2, "      code93:");
    c = encode6(dcode);
    if(c < 0 || (c != 0x00f && c != 0x0f0))
        return(ZBAR_NONE);

    dir = (c >> 7);

    if(dir) {
        if(decode_e(pair_width(dcode, 0), s, 9))
            return(ZBAR_NONE);
        qz = get_width(dcode, 8);
    }

    qz = get_width(dcode, 7);
    if(qz && qz < (s * 3) / 4) {
        dbprintf(2, " [invalid qz %d]", qz);
        return(ZBAR_NONE);
    }

    /* decoded valid start/stop - initialize state */
    dcode93->direction = dir;
    dcode93->element = (!dir) ? 0 : 7;
    dcode93->character = 0;
    dcode93->width = s;

    dbprintf(2, " dir=%x [valid start]", dir);
    return(ZBAR_PARTIAL);
}