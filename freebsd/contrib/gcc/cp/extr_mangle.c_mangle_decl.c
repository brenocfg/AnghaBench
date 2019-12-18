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

/* Variables and functions */
 int /*<<< orphan*/  SET_DECL_ASSEMBLER_NAME (int /*<<< orphan*/  const,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_identifier_nocopy (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mangle_decl_string (int /*<<< orphan*/  const) ; 

void
mangle_decl (const tree decl)
{
  SET_DECL_ASSEMBLER_NAME (decl,
			   get_identifier_nocopy (mangle_decl_string (decl)));
}