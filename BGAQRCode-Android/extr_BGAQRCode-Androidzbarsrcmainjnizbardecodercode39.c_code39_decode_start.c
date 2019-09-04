#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int s9; int direction; int element; scalar_t__ character; } ;
struct TYPE_6__ {TYPE_2__ code39; } ;
typedef  TYPE_1__ zbar_decoder_t ;
typedef  TYPE_2__ code39_decoder_t ;

/* Variables and functions */
 char ZBAR_NONE ; 
 char ZBAR_PARTIAL ; 
 char code39_decode9 (TYPE_1__*) ; 
 int /*<<< orphan*/  dbprintf (int,char*,...) ; 
 unsigned int get_width (TYPE_1__*,int) ; 

__attribute__((used)) static inline signed char code39_decode_start (zbar_decoder_t *dcode)
{
    code39_decoder_t *dcode39 = &dcode->code39;
    dbprintf(2, " s=%d ", dcode39->s9);

    signed char c = code39_decode9(dcode);
    if(c != 0x19 && c != 0x2b) {
        dbprintf(2, "\n");
        return(ZBAR_NONE);
    }
    dcode39->direction ^= (c == 0x19);

    /* check leading quiet zone - spec is 10x */
    unsigned quiet = get_width(dcode, 9);
    if(quiet && quiet < dcode39->s9 / 2) {
        dbprintf(2, " [invalid quiet]\n");
        return(ZBAR_NONE);
    }

    dcode39->element = 9;
    dcode39->character = 0;
    dbprintf(1, " dir=%x [valid start]\n", dcode39->direction);
    return(ZBAR_PARTIAL);
}