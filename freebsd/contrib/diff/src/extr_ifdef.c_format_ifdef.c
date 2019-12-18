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
struct group {void* upto; void* from; int /*<<< orphan*/ * file; } ;
typedef  void* lin ;

/* Variables and functions */
 int /*<<< orphan*/ * files ; 
 int /*<<< orphan*/  format_group (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ,struct group*) ; 
 int /*<<< orphan*/  outfile ; 

__attribute__((used)) static void
format_ifdef (char const *format, lin beg0, lin end0, lin beg1, lin end1)
{
  struct group groups[2];

  groups[0].file = &files[0];
  groups[0].from = beg0;
  groups[0].upto = end0;
  groups[1].file = &files[1];
  groups[1].from = beg1;
  groups[1].upto = end1;
  format_group (outfile, format, 0, groups);
}