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
struct TYPE_3__ {int bitbuf; int bitcount; } ;
typedef  TYPE_1__ bit_stream ;

/* Variables and functions */
 int lword (unsigned char*) ; 

__attribute__((used)) static void bit_advance (bit_stream *bs, int n, unsigned char **p) {
    bs->bitbuf >>= n;
    bs->bitcount -= n;
    if (bs->bitcount < 16) {
	(*p) += 2;
	bs->bitbuf |= (lword(*p)<<bs->bitcount);
	bs->bitcount += 16;
    }
}