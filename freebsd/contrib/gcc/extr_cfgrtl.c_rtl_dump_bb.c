#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ rtx ;
typedef  TYPE_3__* basic_block ;
struct TYPE_8__ {TYPE_1__* rtl; } ;
struct TYPE_9__ {TYPE_2__ il; } ;
struct TYPE_7__ {int /*<<< orphan*/  global_live_at_end; int /*<<< orphan*/  global_live_at_start; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 scalar_t__ BB_END (TYPE_3__*) ; 
 scalar_t__ BB_HEAD (TYPE_3__*) ; 
 scalar_t__ NEXT_INSN (scalar_t__) ; 
 char* alloca (size_t) ; 
 int /*<<< orphan*/  dump_regset (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ *,char*,char*) ; 
 int /*<<< orphan*/  memset (char*,char,size_t) ; 
 int /*<<< orphan*/  print_rtl_single (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  putc (char,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
rtl_dump_bb (basic_block bb, FILE *outf, int indent)
{
  rtx insn;
  rtx last;
  char *s_indent;

  s_indent = alloca ((size_t) indent + 1);
  memset (s_indent, ' ', (size_t) indent);
  s_indent[indent] = '\0';

  fprintf (outf, ";;%s Registers live at start: ", s_indent);
  dump_regset (bb->il.rtl->global_live_at_start, outf);
  putc ('\n', outf);

  for (insn = BB_HEAD (bb), last = NEXT_INSN (BB_END (bb)); insn != last;
       insn = NEXT_INSN (insn))
    print_rtl_single (outf, insn);

  fprintf (outf, ";;%s Registers live at end: ", s_indent);
  dump_regset (bb->il.rtl->global_live_at_end, outf);
  putc ('\n', outf);
}