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
struct hash_table {int dummy; } ;
typedef  int /*<<< orphan*/  rtx ;

/* Variables and functions */
 scalar_t__ CALL ; 
 scalar_t__ CLOBBER ; 
 scalar_t__ GET_CODE (int /*<<< orphan*/ ) ; 
 scalar_t__ PARALLEL ; 
 int /*<<< orphan*/  PATTERN (int /*<<< orphan*/ ) ; 
 scalar_t__ SET ; 
 int /*<<< orphan*/  XVECEXP (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int XVECLEN (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hash_scan_call (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct hash_table*) ; 
 int /*<<< orphan*/  hash_scan_clobber (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct hash_table*) ; 
 int /*<<< orphan*/  hash_scan_set (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct hash_table*) ; 

__attribute__((used)) static void
hash_scan_insn (rtx insn, struct hash_table *table, int in_libcall_block)
{
  rtx pat = PATTERN (insn);
  int i;

  if (in_libcall_block)
    return;

  /* Pick out the sets of INSN and for other forms of instructions record
     what's been modified.  */

  if (GET_CODE (pat) == SET)
    hash_scan_set (pat, insn, table);
  else if (GET_CODE (pat) == PARALLEL)
    for (i = 0; i < XVECLEN (pat, 0); i++)
      {
	rtx x = XVECEXP (pat, 0, i);

	if (GET_CODE (x) == SET)
	  hash_scan_set (x, insn, table);
	else if (GET_CODE (x) == CLOBBER)
	  hash_scan_clobber (x, insn, table);
	else if (GET_CODE (x) == CALL)
	  hash_scan_call (x, insn, table);
      }

  else if (GET_CODE (pat) == CLOBBER)
    hash_scan_clobber (pat, insn, table);
  else if (GET_CODE (pat) == CALL)
    hash_scan_call (pat, insn, table);
}