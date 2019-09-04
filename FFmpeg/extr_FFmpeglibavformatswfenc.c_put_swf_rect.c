#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  buf ;
struct TYPE_6__ {int /*<<< orphan*/  buf; } ;
typedef  TYPE_1__ PutBitContext ;
typedef  int /*<<< orphan*/  AVIOContext ;

/* Variables and functions */
 int /*<<< orphan*/  avio_write (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  flush_put_bits (TYPE_1__*) ; 
 int /*<<< orphan*/  init_put_bits (TYPE_1__*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  max_nbits (int*,int) ; 
 int /*<<< orphan*/  put_bits (TYPE_1__*,int,int) ; 
 int put_bits_ptr (TYPE_1__*) ; 

__attribute__((used)) static void put_swf_rect(AVIOContext *pb,
                         int xmin, int xmax, int ymin, int ymax)
{
    PutBitContext p;
    uint8_t buf[256];
    int nbits, mask;

    init_put_bits(&p, buf, sizeof(buf));

    nbits = 0;
    max_nbits(&nbits, xmin);
    max_nbits(&nbits, xmax);
    max_nbits(&nbits, ymin);
    max_nbits(&nbits, ymax);
    mask = (1 << nbits) - 1;

    /* rectangle info */
    put_bits(&p, 5, nbits);
    put_bits(&p, nbits, xmin & mask);
    put_bits(&p, nbits, xmax & mask);
    put_bits(&p, nbits, ymin & mask);
    put_bits(&p, nbits, ymax & mask);

    flush_put_bits(&p);
    avio_write(pb, buf, put_bits_ptr(&p) - p.buf);
}