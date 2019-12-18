#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_5__ ;
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
struct TYPE_14__ {int /*<<< orphan*/  str; } ;
struct TYPE_15__ {scalar_t__ type; TYPE_3__ val; } ;
typedef  TYPE_4__ cpp_token ;
struct TYPE_13__ {int /*<<< orphan*/  (* ident ) (TYPE_5__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ;} ;
struct TYPE_16__ {int /*<<< orphan*/  directive_line; TYPE_2__ cb; TYPE_1__* directive; } ;
typedef  TYPE_5__ cpp_reader ;
struct TYPE_12__ {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  CPP_DL_ERROR ; 
 scalar_t__ CPP_STRING ; 
 int /*<<< orphan*/  check_eol (TYPE_5__*) ; 
 int /*<<< orphan*/  cpp_error (TYPE_5__*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 TYPE_4__* cpp_get_token (TYPE_5__*) ; 
 int /*<<< orphan*/  stub1 (TYPE_5__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
do_ident (cpp_reader *pfile)
{
  const cpp_token *str = cpp_get_token (pfile);

  if (str->type != CPP_STRING)
    cpp_error (pfile, CPP_DL_ERROR, "invalid #%s directive",
	       pfile->directive->name);
  else if (pfile->cb.ident)
    pfile->cb.ident (pfile, pfile->directive_line, &str->val.str);

  check_eol (pfile);
}