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
struct H263Info {int src; int i; int u; int s; int a; int tr; } ;
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

__attribute__((used)) static void send_mode_a(AVFormatContext *s1, const struct H263Info *info,
                        const uint8_t *buf, int len, int ebits, int m)
{
    RTPMuxContext *s = s1->priv_data;
    PutBitContext pb;

    init_put_bits(&pb, s->buf, 32);
    put_bits(&pb, 1, 0); /* F - 0, mode A */
    put_bits(&pb, 1, 0); /* P - 0, normal I/P */
    put_bits(&pb, 3, 0); /* SBIT - 0 bits */
    put_bits(&pb, 3, ebits); /* EBIT */
    put_bits(&pb, 3, info->src); /* SRC - source format */
    put_bits(&pb, 1, info->i); /* I - inter/intra */
    put_bits(&pb, 1, info->u); /* U - unrestricted motion vector */
    put_bits(&pb, 1, info->s); /* S - syntax-baesd arithmetic coding */
    put_bits(&pb, 1, info->a); /* A - advanced prediction */
    put_bits(&pb, 4, 0); /* R - reserved */
    put_bits(&pb, 2, 0); /* DBQ - 0 */
    put_bits(&pb, 3, 0); /* TRB - 0 */
    put_bits(&pb, 8, info->tr); /* TR */
    flush_put_bits(&pb);
    memcpy(s->buf + 4, buf, len);

    ff_rtp_send_data(s1, s->buf, len + 4, m);
}