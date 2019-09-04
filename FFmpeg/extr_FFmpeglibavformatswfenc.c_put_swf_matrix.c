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

__attribute__((used)) static void put_swf_matrix(AVIOContext *pb,
                           int a, int b, int c, int d, int tx, int ty)
{
    PutBitContext p;
    uint8_t buf[256];
    int nbits;

    init_put_bits(&p, buf, sizeof(buf));

    put_bits(&p, 1, 1); /* a, d present */
    nbits = 1;
    max_nbits(&nbits, a);
    max_nbits(&nbits, d);
    put_bits(&p, 5, nbits); /* nb bits */
    put_bits(&p, nbits, a);
    put_bits(&p, nbits, d);

    put_bits(&p, 1, 1); /* b, c present */
    nbits = 1;
    max_nbits(&nbits, c);
    max_nbits(&nbits, b);
    put_bits(&p, 5, nbits); /* nb bits */
    put_bits(&p, nbits, c);
    put_bits(&p, nbits, b);

    nbits = 1;
    max_nbits(&nbits, tx);
    max_nbits(&nbits, ty);
    put_bits(&p, 5, nbits); /* nb bits */
    put_bits(&p, nbits, tx);
    put_bits(&p, nbits, ty);

    flush_put_bits(&p);
    avio_write(pb, buf, put_bits_ptr(&p) - p.buf);
}