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
typedef  int /*<<< orphan*/  wchar_t ;
typedef  int /*<<< orphan*/  UINT ;
typedef  int /*<<< orphan*/  FOLDER ;
typedef  int /*<<< orphan*/  CFG_RW ;

/* Variables and functions */
 int CfgSaveExW3 (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IsFileExistsW (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SAVE_BINARY_FILE_NAME_SWITCH ; 

bool CfgSaveExW2(CFG_RW *rw, FOLDER *f, wchar_t *name, UINT *written_size)
{
	return CfgSaveExW3(rw, f, name, written_size, IsFileExistsW(SAVE_BINARY_FILE_NAME_SWITCH));
}