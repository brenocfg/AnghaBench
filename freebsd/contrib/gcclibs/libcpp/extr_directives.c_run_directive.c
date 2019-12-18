#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_7__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uchar ;
struct TYPE_12__ {TYPE_7__* directive; } ;
typedef  TYPE_1__ cpp_reader ;
struct TYPE_13__ {int /*<<< orphan*/  (* handler ) (TYPE_1__*) ;} ;

/* Variables and functions */
 scalar_t__ CPP_OPTION (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _cpp_clean_line (TYPE_1__*) ; 
 int /*<<< orphan*/  _cpp_pop_buffer (TYPE_1__*) ; 
 int /*<<< orphan*/  cpp_push_buffer (TYPE_1__*,int /*<<< orphan*/  const*,size_t,int) ; 
 TYPE_7__* dtable ; 
 int /*<<< orphan*/  end_directive (TYPE_1__*,int) ; 
 int /*<<< orphan*/  prepare_directive_trad (TYPE_1__*) ; 
 int /*<<< orphan*/  start_directive (TYPE_1__*) ; 
 int /*<<< orphan*/  stub1 (TYPE_1__*) ; 
 int /*<<< orphan*/  traditional ; 

__attribute__((used)) static void
run_directive (cpp_reader *pfile, int dir_no, const char *buf, size_t count)
{
  cpp_push_buffer (pfile, (const uchar *) buf, count,
		   /* from_stage3 */ true);
  start_directive (pfile);

  /* This is a short-term fix to prevent a leading '#' being
     interpreted as a directive.  */
  _cpp_clean_line (pfile);

  pfile->directive = &dtable[dir_no];
  if (CPP_OPTION (pfile, traditional))
    prepare_directive_trad (pfile);
  pfile->directive->handler (pfile);
  end_directive (pfile, 1);
  _cpp_pop_buffer (pfile);
}