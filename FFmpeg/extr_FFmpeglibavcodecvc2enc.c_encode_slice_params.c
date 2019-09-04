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
struct TYPE_3__ {int /*<<< orphan*/  size_scaler; int /*<<< orphan*/  pb; int /*<<< orphan*/  prefix_bytes; int /*<<< orphan*/  num_y; int /*<<< orphan*/  num_x; } ;
typedef  TYPE_1__ VC2EncContext ;

/* Variables and functions */
 int /*<<< orphan*/  put_vc2_ue_uint (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void encode_slice_params(VC2EncContext *s)
{
    put_vc2_ue_uint(&s->pb, s->num_x);
    put_vc2_ue_uint(&s->pb, s->num_y);
    put_vc2_ue_uint(&s->pb, s->prefix_bytes);
    put_vc2_ue_uint(&s->pb, s->size_scaler);
}