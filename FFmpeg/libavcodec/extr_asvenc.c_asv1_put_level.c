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
typedef  int /*<<< orphan*/  PutBitContext ;

/* Variables and functions */
 int /*<<< orphan*/ ** ff_asv_level_tab ; 
 int /*<<< orphan*/  put_bits (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  put_sbits (int /*<<< orphan*/ *,int,int) ; 

__attribute__((used)) static inline void asv1_put_level(PutBitContext *pb, int level)
{
    unsigned int index = level + 3;

    if (index <= 6) {
        put_bits(pb, ff_asv_level_tab[index][1], ff_asv_level_tab[index][0]);
    } else {
        put_bits(pb, ff_asv_level_tab[3][1], ff_asv_level_tab[3][0]);
        put_sbits(pb, 8, level);
    }
}