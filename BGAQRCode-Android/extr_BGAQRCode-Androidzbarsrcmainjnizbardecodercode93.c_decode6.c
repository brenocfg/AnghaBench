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
struct TYPE_5__ {int /*<<< orphan*/  character; int /*<<< orphan*/  direction; } ;
struct TYPE_6__ {TYPE_1__ code93; int /*<<< orphan*/  buf; } ;
typedef  TYPE_2__ zbar_decoder_t ;

/* Variables and functions */
 int /*<<< orphan*/  _zbar_decoder_buf_dump (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int* code93_hash ; 
 int /*<<< orphan*/  dbprintf (int,char*,int,int,int) ; 
 int encode6 (TYPE_2__*) ; 
 scalar_t__ validate_sig (int) ; 
 int /*<<< orphan*/  zassert (int,int,char*,int /*<<< orphan*/ ,int,int,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline int
decode6 (zbar_decoder_t *dcode)
{
    int sig = encode6(dcode);
    int g0, g1, c;
    if(sig < 0 ||
       (sig & 0x3) + ((sig >> 4) & 0x3) + ((sig >> 8) & 0x3) != 3 ||
       validate_sig(sig))
        return(-1);

    if(dcode->code93.direction) {
        /* reverse signature */
        unsigned tmp = sig & 0x030;
        sig = ((sig & 0x3c0) >> 6) | ((sig & 0x00f) << 6);
        sig = ((sig & 0x30c) >> 2) | ((sig & 0x0c3) << 2) | tmp;
    }

    g0 = code93_hash[(sig - (sig >> 4)) & 0x3f];
    g1 = code93_hash[((sig >> 2) - (sig >> 7)) & 0x3f];
    zassert(g0 >= 0 && g1 >= 0, -1,
            "dir=%x sig=%03x g0=%03x g1=%03x %s\n",
            dcode->code93.direction, sig, g0, g1,
            _zbar_decoder_buf_dump(dcode->buf, dcode->code93.character));

    c = (g0 + g1) & 0x3f;
    dbprintf(2, " g0=%x g1=%x c=%02x", g0, g1, c);
    return(c);
}