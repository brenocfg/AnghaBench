#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  gb; int /*<<< orphan*/ * tonal_scf; int /*<<< orphan*/  avctx; } ;
struct TYPE_6__ {scalar_t__ id; int /*<<< orphan*/  len; int /*<<< orphan*/  data; } ;
typedef  TYPE_1__ LBRChunk ;
typedef  TYPE_2__ DCALbrDecoder ;

/* Variables and functions */
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 scalar_t__ LBR_CHUNK_SCF ; 
 scalar_t__ LBR_CHUNK_TONAL ; 
 scalar_t__ LBR_CHUNK_TONAL_SCF ; 
 int /*<<< orphan*/  av_log (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  get_bits (int /*<<< orphan*/ *,int) ; 
 int get_bits_left (int /*<<< orphan*/ *) ; 
 scalar_t__ init_get_bits8 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ parse_tonal (TYPE_2__*,int) ; 

__attribute__((used)) static int parse_tonal_chunk(DCALbrDecoder *s, LBRChunk *chunk)
{
    int sb, group;

    if (!chunk->len)
        return 0;

    if (init_get_bits8(&s->gb, chunk->data, chunk->len) < 0)
        return -1;

    // Scale factors
    if (chunk->id == LBR_CHUNK_SCF || chunk->id == LBR_CHUNK_TONAL_SCF) {
        if (get_bits_left(&s->gb) < 36) {
            av_log(s->avctx, AV_LOG_ERROR, "Tonal scale factor chunk too short\n");
            return -1;
        }
        for (sb = 0; sb < 6; sb++)
            s->tonal_scf[sb] = get_bits(&s->gb, 6);
    }

    // Tonal groups
    if (chunk->id == LBR_CHUNK_TONAL || chunk->id == LBR_CHUNK_TONAL_SCF)
        for (group = 0; group < 5; group++)
            if (parse_tonal(s, group) < 0)
                return -1;

    return 0;
}