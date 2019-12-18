#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_5__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int int16_t ;
struct TYPE_9__ {int /*<<< orphan*/  table; } ;
struct TYPE_8__ {int /*<<< orphan*/  table; } ;
struct TYPE_6__ {size_t* permutated; } ;
struct TYPE_7__ {int* intra_matrix; int /*<<< orphan*/  gb; TYPE_1__ scantable; } ;
typedef  TYPE_2__ ASV1Context ;

/* Variables and functions */
 int /*<<< orphan*/  VLC_BITS ; 
 TYPE_5__ ac_ccp_vlc ; 
 int asv2_get_bits (int /*<<< orphan*/ *,int) ; 
 int asv2_get_level (int /*<<< orphan*/ *) ; 
 TYPE_3__ dc_ccp_vlc ; 
 void* get_vlc2 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static inline int asv2_decode_block(ASV1Context *a, int16_t block[64])
{
    int i, count, ccp;

    count = asv2_get_bits(&a->gb, 4);

    block[0] = 8 * asv2_get_bits(&a->gb, 8);

    ccp = get_vlc2(&a->gb, dc_ccp_vlc.table, VLC_BITS, 1);
    if (ccp) {
        if (ccp & 4)
            block[a->scantable.permutated[1]] = (asv2_get_level(&a->gb) * a->intra_matrix[1]) >> 4;
        if (ccp & 2)
            block[a->scantable.permutated[2]] = (asv2_get_level(&a->gb) * a->intra_matrix[2]) >> 4;
        if (ccp & 1)
            block[a->scantable.permutated[3]] = (asv2_get_level(&a->gb) * a->intra_matrix[3]) >> 4;
    }

    for (i = 1; i < count + 1; i++) {
        const int ccp = get_vlc2(&a->gb, ac_ccp_vlc.table, VLC_BITS, 1);

        if (ccp) {
            if (ccp & 8)
                block[a->scantable.permutated[4 * i + 0]] = (asv2_get_level(&a->gb) * a->intra_matrix[4 * i + 0]) >> 4;
            if (ccp & 4)
                block[a->scantable.permutated[4 * i + 1]] = (asv2_get_level(&a->gb) * a->intra_matrix[4 * i + 1]) >> 4;
            if (ccp & 2)
                block[a->scantable.permutated[4 * i + 2]] = (asv2_get_level(&a->gb) * a->intra_matrix[4 * i + 2]) >> 4;
            if (ccp & 1)
                block[a->scantable.permutated[4 * i + 3]] = (asv2_get_level(&a->gb) * a->intra_matrix[4 * i + 3]) >> 4;
        }
    }

    return 0;
}