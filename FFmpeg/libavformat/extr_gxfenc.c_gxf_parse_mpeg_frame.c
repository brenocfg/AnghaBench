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
typedef  int uint8_t ;
typedef  int uint32_t ;
struct TYPE_3__ {int first_gop_closed; } ;
typedef  TYPE_1__ GXFStreamContext ;

/* Variables and functions */

__attribute__((used)) static int gxf_parse_mpeg_frame(GXFStreamContext *sc, const uint8_t *buf, int size)
{
    uint32_t c=-1;
    int i;
    for(i=0; i<size-4 && c!=0x100; i++){
        c = (c<<8) + buf[i];
        if(c == 0x1B8 && sc->first_gop_closed == -1) /* GOP start code */
            sc->first_gop_closed= (buf[i+4]>>6)&1;
    }
    return (buf[i+1]>>3)&7;
}