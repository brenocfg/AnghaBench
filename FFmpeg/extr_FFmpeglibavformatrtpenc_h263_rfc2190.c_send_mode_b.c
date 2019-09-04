#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
struct H263State {int quant; int gobn; int mba; int hmv1; int vmv1; int hmv2; int vmv2; } ;
struct H263Info {int src; int i; int u; int s; int a; } ;
struct TYPE_6__ {TYPE_1__* priv_data; } ;
struct TYPE_5__ {scalar_t__ buf; } ;
typedef  TYPE_1__ RTPMuxContext ;
typedef  int /*<<< orphan*/  PutBitContext ;
typedef  TYPE_2__ AVFormatContext ;

/* Variables and functions */
 int /*<<< orphan*/  ff_rtp_send_data (TYPE_2__*,scalar_t__,int,int) ; 
 int /*<<< orphan*/  flush_put_bits (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  init_put_bits (int /*<<< orphan*/ *,scalar_t__,int) ; 
 int /*<<< orphan*/  memcpy (scalar_t__,int /*<<< orphan*/  const*,int) ; 
 int /*<<< orphan*/  put_bits (int /*<<< orphan*/ *,int,int) ; 

__attribute__((used)) static void send_mode_b(AVFormatContext *s1, const struct H263Info *info,
                        const struct H263State *state, const uint8_t *buf,
                        int len, int sbits, int ebits, int m)
{
    RTPMuxContext *s = s1->priv_data;
    PutBitContext pb;

    init_put_bits(&pb, s->buf, 64);
    put_bits(&pb, 1, 1); /* F - 1, mode B */
    put_bits(&pb, 1, 0); /* P - 0, mode B */
    put_bits(&pb, 3, sbits); /* SBIT - 0 bits */
    put_bits(&pb, 3, ebits); /* EBIT - 0 bits */
    put_bits(&pb, 3, info->src); /* SRC - source format */
    put_bits(&pb, 5, state->quant); /* QUANT - quantizer for the first MB */
    put_bits(&pb, 5, state->gobn); /* GOBN - GOB number */
    put_bits(&pb, 9, state->mba); /* MBA - MB address */
    put_bits(&pb, 2, 0); /* R - reserved */
    put_bits(&pb, 1, info->i); /* I - inter/intra */
    put_bits(&pb, 1, info->u); /* U - unrestricted motion vector */
    put_bits(&pb, 1, info->s); /* S - syntax-baesd arithmetic coding */
    put_bits(&pb, 1, info->a); /* A - advanced prediction */
    put_bits(&pb, 7, state->hmv1); /* HVM1 - horizontal motion vector 1 */
    put_bits(&pb, 7, state->vmv1); /* VMV1 - vertical motion vector 1 */
    put_bits(&pb, 7, state->hmv2); /* HVM2 - horizontal motion vector 2 */
    put_bits(&pb, 7, state->vmv2); /* VMV2 - vertical motion vector 2 */
    flush_put_bits(&pb);
    memcpy(s->buf + 8, buf, len);

    ff_rtp_send_data(s1, s->buf, len + 8, m);
}