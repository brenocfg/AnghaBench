#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
struct TYPE_13__ {int /*<<< orphan*/  gb; int /*<<< orphan*/  num_vectors; } ;
struct TYPE_12__ {int total_subbands; int /*<<< orphan*/  log2_numvector_size; } ;
typedef  TYPE_1__ COOKSubpacket ;
typedef  TYPE_2__ COOKContext ;

/* Variables and functions */
 int AVERROR_INVALIDDATA ; 
 int /*<<< orphan*/  categorize (TYPE_2__*,TYPE_1__*,int*,int*,int*) ; 
 int decode_envelope (TYPE_2__*,TYPE_1__*,int*) ; 
 int /*<<< orphan*/  decode_vectors (TYPE_2__*,TYPE_1__*,int*,int*,float*) ; 
 int /*<<< orphan*/  expand_category (TYPE_2__*,int*,int*) ; 
 int /*<<< orphan*/  get_bits (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int mono_decode(COOKContext *q, COOKSubpacket *p, float *mlt_buffer)
{
    int category_index[128] = { 0 };
    int category[128]       = { 0 };
    int quant_index_table[102];
    int res, i;

    if ((res = decode_envelope(q, p, quant_index_table)) < 0)
        return res;
    q->num_vectors = get_bits(&q->gb, p->log2_numvector_size);
    categorize(q, p, quant_index_table, category, category_index);
    expand_category(q, category, category_index);
    for (i=0; i<p->total_subbands; i++) {
        if (category[i] > 7)
            return AVERROR_INVALIDDATA;
    }
    decode_vectors(q, p, category, quant_index_table, mlt_buffer);

    return 0;
}