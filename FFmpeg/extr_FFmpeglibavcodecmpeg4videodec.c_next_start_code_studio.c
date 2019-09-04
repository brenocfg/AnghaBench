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
typedef  int /*<<< orphan*/  GetBitContext ;

/* Variables and functions */
 int /*<<< orphan*/  align_get_bits (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  get_bits (int /*<<< orphan*/ *,int) ; 
 int get_bits_left (int /*<<< orphan*/ *) ; 
 int show_bits_long (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void next_start_code_studio(GetBitContext *gb)
{
    align_get_bits(gb);

    while (get_bits_left(gb) >= 24 && show_bits_long(gb, 24) != 0x1) {
        get_bits(gb, 8);
    }
}