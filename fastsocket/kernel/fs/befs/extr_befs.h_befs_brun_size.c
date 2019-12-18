#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_3__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct super_block {int dummy; } ;
struct TYPE_4__ {size_t len; } ;
typedef  TYPE_1__ befs_block_run ;
struct TYPE_5__ {size_t block_size; } ;

/* Variables and functions */
 TYPE_3__* BEFS_SB (struct super_block*) ; 

__attribute__((used)) static inline size_t
befs_brun_size(struct super_block *sb, befs_block_run run)
{
	return BEFS_SB(sb)->block_size * run.len;
}