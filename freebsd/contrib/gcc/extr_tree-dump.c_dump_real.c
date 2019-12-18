#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* dump_info_p ;
typedef  int /*<<< orphan*/  buf ;
struct TYPE_4__ {int /*<<< orphan*/  column; int /*<<< orphan*/  stream; } ;
typedef  int /*<<< orphan*/  REAL_VALUE_TYPE ;

/* Variables and functions */
 int /*<<< orphan*/  dump_maybe_newline (TYPE_1__*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char const*,char*) ; 
 int /*<<< orphan*/  real_to_decimal (char*,int /*<<< orphan*/  const*,int,int /*<<< orphan*/ ,int) ; 
 scalar_t__ strlen (char*) ; 

__attribute__((used)) static void
dump_real (dump_info_p di, const char *field, const REAL_VALUE_TYPE *r)
{
  char buf[32];
  real_to_decimal (buf, r, sizeof (buf), 0, true);
  dump_maybe_newline (di);
  fprintf (di->stream, "%-4s: %s ", field, buf);
  di->column += strlen (buf) + 7;
}