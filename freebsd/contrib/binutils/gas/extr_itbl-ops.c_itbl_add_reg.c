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
struct itbl_entry {int dummy; } ;

/* Variables and functions */
 struct itbl_entry* alloc_entry (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,unsigned long) ; 
 int /*<<< orphan*/  get_processor (int) ; 
 int /*<<< orphan*/  get_type (int) ; 

struct itbl_entry *
itbl_add_reg (int yyprocessor, int yytype, char *regname,
	      int regnum)
{
  return alloc_entry (get_processor (yyprocessor), get_type (yytype), regname,
		      (unsigned long) regnum);
}