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
struct TYPE_3__ {int chroma_x_shift; int chroma_y_shift; int /*<<< orphan*/  pb; int /*<<< orphan*/  strict_compliance; } ;
typedef  TYPE_1__ VC2EncContext ;

/* Variables and functions */
 int /*<<< orphan*/  put_bits (int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  put_vc2_ue_uint (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void encode_sample_fmt(VC2EncContext *s)
{
    put_bits(&s->pb, 1, !s->strict_compliance);
    if (!s->strict_compliance) {
        int idx;
        if (s->chroma_x_shift == 1 && s->chroma_y_shift == 0)
            idx = 1; /* 422 */
        else if (s->chroma_x_shift == 1 && s->chroma_y_shift == 1)
            idx = 2; /* 420 */
        else
            idx = 0; /* 444 */
        put_vc2_ue_uint(&s->pb, idx);
    }
}