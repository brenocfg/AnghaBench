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
typedef  int uint16_t ;
typedef  int /*<<< orphan*/  sh2rec_block_t ;

/* Variables and functions */
 int /*<<< orphan*/  EMIT_INST ; 

__attribute__((used)) static inline void emitMOVWI(sh2rec_block_t *b, int d, int n) {
    uint16_t inst = 0x9000 | (n << 8) | (d);
    EMIT_INST;
}