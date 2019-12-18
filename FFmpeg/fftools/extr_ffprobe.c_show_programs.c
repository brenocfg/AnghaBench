#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  WriterContext ;
struct TYPE_6__ {int nb_programs; int /*<<< orphan*/ ** programs; } ;
struct TYPE_5__ {TYPE_2__* fmt_ctx; } ;
typedef  TYPE_1__ InputFile ;
typedef  int /*<<< orphan*/  AVProgram ;
typedef  TYPE_2__ AVFormatContext ;

/* Variables and functions */
 int /*<<< orphan*/  SECTION_ID_PROGRAMS ; 
 int show_program (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  writer_print_section_footer (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  writer_print_section_header (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int show_programs(WriterContext *w, InputFile *ifile)
{
    AVFormatContext *fmt_ctx = ifile->fmt_ctx;
    int i, ret = 0;

    writer_print_section_header(w, SECTION_ID_PROGRAMS);
    for (i = 0; i < fmt_ctx->nb_programs; i++) {
        AVProgram *program = fmt_ctx->programs[i];
        if (!program)
            continue;
        ret = show_program(w, ifile, program);
        if (ret < 0)
            break;
    }
    writer_print_section_footer(w);
    return ret;
}