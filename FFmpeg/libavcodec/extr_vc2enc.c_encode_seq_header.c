#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  interlaced; int /*<<< orphan*/  pb; int /*<<< orphan*/  base_vf; } ;
typedef  TYPE_1__ VC2EncContext ;

/* Variables and functions */
 int /*<<< orphan*/  avpriv_align_put_bits (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  encode_parse_params (TYPE_1__*) ; 
 int /*<<< orphan*/  encode_source_params (TYPE_1__*) ; 
 int /*<<< orphan*/  put_vc2_ue_uint (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void encode_seq_header(VC2EncContext *s)
{
    avpriv_align_put_bits(&s->pb);
    encode_parse_params(s);
    put_vc2_ue_uint(&s->pb, s->base_vf);
    encode_source_params(s);
    put_vc2_ue_uint(&s->pb, s->interlaced); /* Frames or fields coding */
}