#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  WriterContext ;
struct TYPE_7__ {int /*<<< orphan*/  metadata; int /*<<< orphan*/  time_base; int /*<<< orphan*/  end; int /*<<< orphan*/  start; int /*<<< orphan*/  id; } ;
struct TYPE_6__ {int nb_chapters; TYPE_3__** chapters; } ;
struct TYPE_5__ {TYPE_2__* fmt_ctx; } ;
typedef  TYPE_1__ InputFile ;
typedef  TYPE_2__ AVFormatContext ;
typedef  TYPE_3__ AVChapter ;

/* Variables and functions */
 int /*<<< orphan*/  SECTION_ID_CHAPTER ; 
 int /*<<< orphan*/  SECTION_ID_CHAPTERS ; 
 int /*<<< orphan*/  SECTION_ID_CHAPTER_TAGS ; 
 scalar_t__ do_show_chapter_tags ; 
 int /*<<< orphan*/  print_int (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  print_q (char*,int /*<<< orphan*/ ,char) ; 
 int /*<<< orphan*/  print_time (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int show_tags (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  writer_print_section_footer (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  writer_print_section_header (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int show_chapters(WriterContext *w, InputFile *ifile)
{
    AVFormatContext *fmt_ctx = ifile->fmt_ctx;
    int i, ret = 0;

    writer_print_section_header(w, SECTION_ID_CHAPTERS);
    for (i = 0; i < fmt_ctx->nb_chapters; i++) {
        AVChapter *chapter = fmt_ctx->chapters[i];

        writer_print_section_header(w, SECTION_ID_CHAPTER);
        print_int("id", chapter->id);
        print_q  ("time_base", chapter->time_base, '/');
        print_int("start", chapter->start);
        print_time("start_time", chapter->start, &chapter->time_base);
        print_int("end", chapter->end);
        print_time("end_time", chapter->end, &chapter->time_base);
        if (do_show_chapter_tags)
            ret = show_tags(w, chapter->metadata, SECTION_ID_CHAPTER_TAGS);
        writer_print_section_footer(w);
    }
    writer_print_section_footer(w);

    return ret;
}