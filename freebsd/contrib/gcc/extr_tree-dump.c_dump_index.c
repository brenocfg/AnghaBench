#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* dump_info_p ;
struct TYPE_3__ {int column; int /*<<< orphan*/  stream; } ;

/* Variables and functions */
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,unsigned int) ; 

__attribute__((used)) static void
dump_index (dump_info_p di, unsigned int index)
{
  fprintf (di->stream, "@%-6u ", index);
  di->column += 8;
}