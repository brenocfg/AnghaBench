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
 char* ANON_AGGRNAME_FORMAT ; 
 int /*<<< orphan*/  anon_cnt ; 
 int /*<<< orphan*/  get_identifier (char*) ; 
 int /*<<< orphan*/  sprintf (char*,char*,int /*<<< orphan*/ ) ; 

tree
make_anon_name (void)
{
  char buf[32];

  sprintf (buf, ANON_AGGRNAME_FORMAT, anon_cnt++);
  return get_identifier (buf);
}