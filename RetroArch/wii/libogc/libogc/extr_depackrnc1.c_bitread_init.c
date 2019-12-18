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
struct TYPE_3__ {int bitcount; int /*<<< orphan*/  bitbuf; } ;
typedef  TYPE_1__ bit_stream ;

/* Variables and functions */
 int /*<<< orphan*/  lword (unsigned char*) ; 

__attribute__((used)) static void bitread_init (bit_stream *bs, unsigned char **p) {
    bs->bitbuf = lword (*p);
    bs->bitcount = 16;
}