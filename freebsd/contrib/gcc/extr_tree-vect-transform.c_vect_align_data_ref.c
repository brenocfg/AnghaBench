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
typedef  int /*<<< orphan*/  tree ;
struct data_reference {int dummy; } ;
typedef  int /*<<< orphan*/  stmt_vec_info ;

/* Variables and functions */
 struct data_reference* STMT_VINFO_DATA_REF (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  aligned_access_p (struct data_reference*) ; 
 int /*<<< orphan*/  gcc_assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vinfo_for_stmt (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
vect_align_data_ref (tree stmt)
{
  stmt_vec_info stmt_info = vinfo_for_stmt (stmt);
  struct data_reference *dr = STMT_VINFO_DATA_REF (stmt_info);

  /* FORNOW: can't handle misaligned accesses; 
             all accesses expected to be aligned.  */
  gcc_assert (aligned_access_p (dr));
}