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
typedef  int int16_t ;
struct TYPE_3__ {int* q_intra_matrix; int /*<<< orphan*/  pb; } ;
typedef  TYPE_1__ ASV1Context ;

/* Variables and functions */
 int /*<<< orphan*/  asv1_put_level (int /*<<< orphan*/ *,int) ; 
 int** ff_asv_ccp_tab ; 
 int* ff_asv_scantab ; 
 int /*<<< orphan*/  put_bits (int /*<<< orphan*/ *,int,int) ; 

__attribute__((used)) static inline void asv1_encode_block(ASV1Context *a, int16_t block[64])
{
    int i;
    int nc_count = 0;

    put_bits(&a->pb, 8, (block[0] + 32) >> 6);
    block[0] = 0;

    for (i = 0; i < 10; i++) {
        const int index = ff_asv_scantab[4 * i];
        int ccp         = 0;

        if ((block[index + 0] = (block[index + 0] *
                                 a->q_intra_matrix[index + 0] + (1 << 15)) >> 16))
            ccp |= 8;
        if ((block[index + 8] = (block[index + 8] *
                                 a->q_intra_matrix[index + 8] + (1 << 15)) >> 16))
            ccp |= 4;
        if ((block[index + 1] = (block[index + 1] *
                                 a->q_intra_matrix[index + 1] + (1 << 15)) >> 16))
            ccp |= 2;
        if ((block[index + 9] = (block[index + 9] *
                                 a->q_intra_matrix[index + 9] + (1 << 15)) >> 16))
            ccp |= 1;

        if (ccp) {
            for (; nc_count; nc_count--)
                put_bits(&a->pb, ff_asv_ccp_tab[0][1], ff_asv_ccp_tab[0][0]);

            put_bits(&a->pb, ff_asv_ccp_tab[ccp][1], ff_asv_ccp_tab[ccp][0]);

            if (ccp & 8)
                asv1_put_level(&a->pb, block[index + 0]);
            if (ccp & 4)
                asv1_put_level(&a->pb, block[index + 8]);
            if (ccp & 2)
                asv1_put_level(&a->pb, block[index + 1]);
            if (ccp & 1)
                asv1_put_level(&a->pb, block[index + 9]);
        } else {
            nc_count++;
        }
    }
    put_bits(&a->pb, ff_asv_ccp_tab[16][1], ff_asv_ccp_tab[16][0]);
}