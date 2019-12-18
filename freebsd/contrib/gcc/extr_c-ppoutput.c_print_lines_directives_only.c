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
struct TYPE_2__ {int src_line; int /*<<< orphan*/  outf; } ;

/* Variables and functions */
 int /*<<< orphan*/  fwrite (void const*,int,size_t,int /*<<< orphan*/ ) ; 
 TYPE_1__ print ; 

__attribute__((used)) static void
print_lines_directives_only (int lines, const void *buf, size_t size)
{
  print.src_line += lines;
  fwrite (buf, 1, size, print.outf);
}