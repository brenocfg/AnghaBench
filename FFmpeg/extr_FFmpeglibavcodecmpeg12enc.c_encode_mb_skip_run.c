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
struct TYPE_3__ {int /*<<< orphan*/  pb; } ;
typedef  TYPE_1__ MpegEncContext ;

/* Variables and functions */
 int** ff_mpeg12_mbAddrIncrTable ; 
 int /*<<< orphan*/  put_bits (int /*<<< orphan*/ *,int,int) ; 

__attribute__((used)) static inline void encode_mb_skip_run(MpegEncContext *s, int run)
{
    while (run >= 33) {
        put_bits(&s->pb, 11, 0x008);
        run -= 33;
    }
    put_bits(&s->pb, ff_mpeg12_mbAddrIncrTable[run][1],
             ff_mpeg12_mbAddrIncrTable[run][0]);
}