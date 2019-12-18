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
typedef  int uint16_t ;
struct TYPE_8__ {scalar_t__ eof_reached; } ;
struct TYPE_7__ {scalar_t__ probesize; TYPE_2__* pb; } ;
typedef  TYPE_1__ AVFormatContext ;

/* Variables and functions */
 int AVERROR_EOF ; 
 int AVERROR_INVALIDDATA ; 
 int /*<<< orphan*/  SEEK_CUR ; 
 int /*<<< orphan*/  avio_feof (TYPE_2__*) ; 
 int avio_r8 (TYPE_2__*) ; 
 int /*<<< orphan*/  avio_seek (TYPE_2__*,int,int /*<<< orphan*/ ) ; 
 scalar_t__ avio_tell (TYPE_2__*) ; 

__attribute__((used)) static int adts_aac_resync(AVFormatContext *s)
{
    uint16_t state;

    // skip data until an ADTS frame is found
    state = avio_r8(s->pb);
    while (!avio_feof(s->pb) && avio_tell(s->pb) < s->probesize) {
        state = (state << 8) | avio_r8(s->pb);
        if ((state >> 4) != 0xFFF)
            continue;
        avio_seek(s->pb, -2, SEEK_CUR);
        break;
    }
    if (s->pb->eof_reached)
        return AVERROR_EOF;
    if ((state >> 4) != 0xFFF)
        return AVERROR_INVALIDDATA;

    return 0;
}