#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int /*<<< orphan*/  int16_t ;
typedef  int /*<<< orphan*/  VLC ;
typedef  int /*<<< orphan*/  Node ;

/* Variables and functions */
 int FF_HUFFMAN_FLAG_ZERO_COUNT ; 
 int ff_init_vlc_sparse (int /*<<< orphan*/ *,int,int,int /*<<< orphan*/ *,int,int,int /*<<< orphan*/ *,int,int,int /*<<< orphan*/ *,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_tree_codes (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int) ; 

__attribute__((used)) static int build_huff_tree(VLC *vlc, Node *nodes, int head, int flags, int nb_bits)
{
    int no_zero_count = !(flags & FF_HUFFMAN_FLAG_ZERO_COUNT);
    uint32_t bits[256];
    int16_t lens[256];
    uint8_t xlat[256];
    int pos = 0;

    get_tree_codes(bits, lens, xlat, nodes, head, 0, 0,
                   &pos, no_zero_count);
    return ff_init_vlc_sparse(vlc, nb_bits, pos, lens, 2, 2, bits, 4, 4, xlat, 1, 1, 0);
}