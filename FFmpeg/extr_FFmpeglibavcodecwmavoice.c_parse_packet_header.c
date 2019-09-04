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
struct TYPE_3__ {int spillover_bitsize; void* spillover_nbits; int /*<<< orphan*/  has_residual_lsps; int /*<<< orphan*/  gb; } ;
typedef  TYPE_1__ WMAVoiceContext ;
typedef  int /*<<< orphan*/  GetBitContext ;

/* Variables and functions */
 int AVERROR_INVALIDDATA ; 
 void* get_bits (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  get_bits1 (int /*<<< orphan*/ *) ; 
 scalar_t__ get_bits_left (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  skip_bits (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int parse_packet_header(WMAVoiceContext *s)
{
    GetBitContext *gb = &s->gb;
    unsigned int res, n_superframes = 0;

    skip_bits(gb, 4);          // packet sequence number
    s->has_residual_lsps = get_bits1(gb);
    do {
        res = get_bits(gb, 6); // number of superframes per packet
                               // (minus first one if there is spillover)
        n_superframes += res;
    } while (res == 0x3F);
    s->spillover_nbits   = get_bits(gb, s->spillover_bitsize);

    return get_bits_left(gb) >= 0 ? n_superframes : AVERROR_INVALIDDATA;
}