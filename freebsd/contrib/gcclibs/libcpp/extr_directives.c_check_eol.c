#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_5__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {TYPE_1__* directive; } ;
typedef  TYPE_2__ cpp_reader ;
struct TYPE_9__ {scalar_t__ type; } ;
struct TYPE_7__ {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  CPP_DL_PEDWARN ; 
 scalar_t__ CPP_EOF ; 
 int /*<<< orphan*/  SEEN_EOL () ; 
 TYPE_5__* _cpp_lex_token (TYPE_2__*) ; 
 int /*<<< orphan*/  cpp_error (TYPE_2__*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
check_eol (cpp_reader *pfile)
{
  if (! SEEN_EOL () && _cpp_lex_token (pfile)->type != CPP_EOF)
    cpp_error (pfile, CPP_DL_PEDWARN, "extra tokens at end of #%s directive",
	       pfile->directive->name);
}