#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  subband_coef_sign ;
typedef  int /*<<< orphan*/  subband_coef_index ;
struct TYPE_9__ {int samples_per_channel; int /*<<< orphan*/  (* scalar_dequant ) (TYPE_2__*,int,int,int*,int*,float*) ;} ;
struct TYPE_8__ {int total_subbands; } ;
typedef  TYPE_1__ COOKSubpacket ;
typedef  TYPE_2__ COOKContext ;

/* Variables and functions */
 int SUBBAND_SIZE ; 
 int /*<<< orphan*/  memset (int*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub1 (TYPE_2__*,int,int,int*,int*,float*) ; 
 scalar_t__ unpack_SQVH (TYPE_2__*,TYPE_1__*,int,int*,int*) ; 

__attribute__((used)) static void decode_vectors(COOKContext *q, COOKSubpacket *p, int *category,
                           int *quant_index_table, float *mlt_buffer)
{
    /* A zero in this table means that the subband coefficient is
       random noise coded. */
    int subband_coef_index[SUBBAND_SIZE];
    /* A zero in this table means that the subband coefficient is a
       positive multiplicator. */
    int subband_coef_sign[SUBBAND_SIZE];
    int band, j;
    int index = 0;

    for (band = 0; band < p->total_subbands; band++) {
        index = category[band];
        if (category[band] < 7) {
            if (unpack_SQVH(q, p, category[band], subband_coef_index, subband_coef_sign)) {
                index = 7;
                for (j = 0; j < p->total_subbands; j++)
                    category[band + j] = 7;
            }
        }
        if (index >= 7) {
            memset(subband_coef_index, 0, sizeof(subband_coef_index));
            memset(subband_coef_sign,  0, sizeof(subband_coef_sign));
        }
        q->scalar_dequant(q, index, quant_index_table[band],
                          subband_coef_index, subband_coef_sign,
                          &mlt_buffer[band * SUBBAND_SIZE]);
    }

    /* FIXME: should this be removed, or moved into loop above? */
    if (p->total_subbands * SUBBAND_SIZE >= q->samples_per_channel)
        return;
}