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
struct TYPE_3__ {int wavelet_depth; int /*<<< orphan*/ ** quant; int /*<<< orphan*/  pb; scalar_t__ custom_quant_matrix; } ;
typedef  TYPE_1__ VC2EncContext ;

/* Variables and functions */
 int /*<<< orphan*/  put_bits (int /*<<< orphan*/ *,int,scalar_t__) ; 
 int /*<<< orphan*/  put_vc2_ue_uint (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void encode_quant_matrix(VC2EncContext *s)
{
    int level;
    put_bits(&s->pb, 1, s->custom_quant_matrix);
    if (s->custom_quant_matrix) {
        put_vc2_ue_uint(&s->pb, s->quant[0][0]);
        for (level = 0; level < s->wavelet_depth; level++) {
            put_vc2_ue_uint(&s->pb, s->quant[level][1]);
            put_vc2_ue_uint(&s->pb, s->quant[level][2]);
            put_vc2_ue_uint(&s->pb, s->quant[level][3]);
        }
    }
}