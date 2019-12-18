#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct super_block {int dummy; } ;
typedef  int /*<<< orphan*/  __le32 ;
typedef  int /*<<< orphan*/  __fs32 ;
typedef  int /*<<< orphan*/  __be32 ;
struct TYPE_2__ {scalar_t__ s_bytesex; } ;

/* Variables and functions */
 scalar_t__ BYTESEX_LE ; 
 TYPE_1__* UFS_SB (struct super_block*) ; 
 int /*<<< orphan*/  be32_add_cpu (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  le32_add_cpu (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static inline void
fs32_sub(struct super_block *sbp, __fs32 *n, int d)
{
	if (UFS_SB(sbp)->s_bytesex == BYTESEX_LE)
		le32_add_cpu((__le32 *)n, -d);
	else
		be32_add_cpu((__be32 *)n, -d);
}