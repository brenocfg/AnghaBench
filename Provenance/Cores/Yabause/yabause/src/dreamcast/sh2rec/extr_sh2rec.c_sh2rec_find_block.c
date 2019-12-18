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
typedef  int /*<<< orphan*/  u32 ;
typedef  int /*<<< orphan*/  sh2rec_block_t ;

/* Variables and functions */
 int /*<<< orphan*/ * sh2rec_htab_block_create (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/ * sh2rec_htab_lookup (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sh2rec_rec_block (int /*<<< orphan*/ *) ; 

sh2rec_block_t *sh2rec_find_block(u32 pc) {
    sh2rec_block_t *b = sh2rec_htab_lookup(pc);

    if(!b) {
        b = sh2rec_htab_block_create(pc, 4096);
        sh2rec_rec_block(b);
    }

    return b;
}