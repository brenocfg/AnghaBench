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
struct TYPE_6__ {int size_in_bits; } ;
typedef  TYPE_1__ PutBitContext ;
typedef  int /*<<< orphan*/  GetBitContext ;

/* Variables and functions */
 int FFMIN (int,int) ; 
 int /*<<< orphan*/  avpriv_copy_bits (TYPE_1__*,int /*<<< orphan*/  const*,int) ; 
 int /*<<< orphan*/  get_bits (int /*<<< orphan*/ *,int) ; 
 int get_bits_left (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  put_bits (TYPE_1__*,int,int /*<<< orphan*/ ) ; 
 int put_bits_count (TYPE_1__*) ; 

__attribute__((used)) static void copy_bits(PutBitContext *pb,
                      const uint8_t *data, int size,
                      GetBitContext *gb, int nbits)
{
    int rmn_bytes, rmn_bits;

    rmn_bits = rmn_bytes = get_bits_left(gb);
    if (rmn_bits < nbits)
        return;
    if (nbits > pb->size_in_bits - put_bits_count(pb))
        return;
    rmn_bits &= 7; rmn_bytes >>= 3;
    if ((rmn_bits = FFMIN(rmn_bits, nbits)) > 0)
        put_bits(pb, rmn_bits, get_bits(gb, rmn_bits));
    avpriv_copy_bits(pb, data + size - rmn_bytes,
                 FFMIN(nbits - rmn_bits, rmn_bytes << 3));
}