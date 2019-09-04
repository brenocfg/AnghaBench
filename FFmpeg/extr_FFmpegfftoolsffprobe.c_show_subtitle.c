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
typedef  int /*<<< orphan*/  WriterContext ;
struct TYPE_3__ {int /*<<< orphan*/  num_rects; int /*<<< orphan*/  end_display_time; int /*<<< orphan*/  start_display_time; int /*<<< orphan*/  format; int /*<<< orphan*/  pts; } ;
typedef  TYPE_1__ AVSubtitle ;
typedef  int /*<<< orphan*/  AVStream ;
typedef  int /*<<< orphan*/  AVFormatContext ;
typedef  int /*<<< orphan*/  AVBPrint ;

/* Variables and functions */
 int /*<<< orphan*/  AV_BPRINT_SIZE_UNLIMITED ; 
 int /*<<< orphan*/  AV_TIME_BASE_Q ; 
 int /*<<< orphan*/  SECTION_ID_SUBTITLE ; 
 int /*<<< orphan*/  av_bprint_finalize (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  av_bprint_init (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fflush (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  print_int (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  print_str (char*,char*) ; 
 int /*<<< orphan*/  print_time (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  print_ts (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stdout ; 
 int /*<<< orphan*/  writer_print_section_footer (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  writer_print_section_header (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void show_subtitle(WriterContext *w, AVSubtitle *sub, AVStream *stream,
                          AVFormatContext *fmt_ctx)
{
    AVBPrint pbuf;

    av_bprint_init(&pbuf, 1, AV_BPRINT_SIZE_UNLIMITED);

    writer_print_section_header(w, SECTION_ID_SUBTITLE);

    print_str ("media_type",         "subtitle");
    print_ts  ("pts",                 sub->pts);
    print_time("pts_time",            sub->pts, &AV_TIME_BASE_Q);
    print_int ("format",              sub->format);
    print_int ("start_display_time",  sub->start_display_time);
    print_int ("end_display_time",    sub->end_display_time);
    print_int ("num_rects",           sub->num_rects);

    writer_print_section_footer(w);

    av_bprint_finalize(&pbuf, NULL);
    fflush(stdout);
}