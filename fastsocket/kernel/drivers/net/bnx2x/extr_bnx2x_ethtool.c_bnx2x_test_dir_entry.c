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
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u32 ;
struct code_entry {int dummy; } ;
struct bnx2x {int dummy; } ;
typedef  int /*<<< orphan*/  entry ;

/* Variables and functions */
 int bnx2x_nvram_read32 (struct bnx2x*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int bnx2x_test_nvram_dir (struct bnx2x*,struct code_entry*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int bnx2x_test_dir_entry(struct bnx2x *bp, u32 addr, u8 *buff)
{
	int rc;
	struct code_entry entry;

	rc = bnx2x_nvram_read32(bp, addr, (u32 *)&entry, sizeof(entry));
	if (rc)
		return rc;

	return bnx2x_test_nvram_dir(bp, &entry, buff);
}