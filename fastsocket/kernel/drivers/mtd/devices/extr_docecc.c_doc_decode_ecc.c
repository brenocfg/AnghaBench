#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int gf ;
typedef  int /*<<< orphan*/  dtype ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int KK ; 
 int NB_DATA ; 
 int NN ; 
 int SECTOR_SIZE ; 
 int eras_dec_rs (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int*,int*,int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  generate_gf (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * kmalloc (int,int /*<<< orphan*/ ) ; 

int doc_decode_ecc(unsigned char sector[SECTOR_SIZE], unsigned char ecc1[6])
{
    int parity, i, nb_errors;
    gf bb[NN - KK + 1];
    gf error_val[NN-KK];
    int error_pos[NN-KK], pos, bitpos, index, val;
    dtype *Alpha_to, *Index_of;

    /* init log and exp tables here to save memory. However, it is slower */
    Alpha_to = kmalloc((NN + 1) * sizeof(dtype), GFP_KERNEL);
    if (!Alpha_to)
        return -1;

    Index_of = kmalloc((NN + 1) * sizeof(dtype), GFP_KERNEL);
    if (!Index_of) {
        kfree(Alpha_to);
        return -1;
    }

    generate_gf(Alpha_to, Index_of);

    parity = ecc1[1];

    bb[0] =  (ecc1[4] & 0xff) | ((ecc1[5] & 0x03) << 8);
    bb[1] = ((ecc1[5] & 0xfc) >> 2) | ((ecc1[2] & 0x0f) << 6);
    bb[2] = ((ecc1[2] & 0xf0) >> 4) | ((ecc1[3] & 0x3f) << 4);
    bb[3] = ((ecc1[3] & 0xc0) >> 6) | ((ecc1[0] & 0xff) << 2);

    nb_errors = eras_dec_rs(Alpha_to, Index_of, bb,
                            error_val, error_pos, 0);
    if (nb_errors <= 0)
        goto the_end;

    /* correct the errors */
    for(i=0;i<nb_errors;i++) {
        pos = error_pos[i];
        if (pos >= NB_DATA && pos < KK) {
            nb_errors = -1;
            goto the_end;
        }
        if (pos < NB_DATA) {
            /* extract bit position (MSB first) */
            pos = 10 * (NB_DATA - 1 - pos) - 6;
            /* now correct the following 10 bits. At most two bytes
               can be modified since pos is even */
            index = (pos >> 3) ^ 1;
            bitpos = pos & 7;
            if ((index >= 0 && index < SECTOR_SIZE) ||
                index == (SECTOR_SIZE + 1)) {
                val = error_val[i] >> (2 + bitpos);
                parity ^= val;
                if (index < SECTOR_SIZE)
                    sector[index] ^= val;
            }
            index = ((pos >> 3) + 1) ^ 1;
            bitpos = (bitpos + 10) & 7;
            if (bitpos == 0)
                bitpos = 8;
            if ((index >= 0 && index < SECTOR_SIZE) ||
                index == (SECTOR_SIZE + 1)) {
                val = error_val[i] << (8 - bitpos);
                parity ^= val;
                if (index < SECTOR_SIZE)
                    sector[index] ^= val;
            }
        }
    }

    /* use parity to test extra errors */
    if ((parity & 0xff) != 0)
        nb_errors = -1;

 the_end:
    kfree(Alpha_to);
    kfree(Index_of);
    return nb_errors;
}