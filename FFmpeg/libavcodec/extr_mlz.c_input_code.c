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
 int get_bits1 (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int input_code(GetBitContext* gb, int len) {
    int tmp_code = 0;
    int i;
    for (i = 0; i < len; ++i) {
        tmp_code |= get_bits1(gb) << i;
    }
    return tmp_code;
}