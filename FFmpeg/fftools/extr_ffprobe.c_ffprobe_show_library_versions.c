#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  WriterContext ;

/* Variables and functions */
 int /*<<< orphan*/  AVCODEC ; 
 int /*<<< orphan*/  AVDEVICE ; 
 int /*<<< orphan*/  AVFILTER ; 
 int /*<<< orphan*/  AVFORMAT ; 
 int /*<<< orphan*/  AVUTIL ; 
 int /*<<< orphan*/  POSTPROC ; 
 int /*<<< orphan*/  SECTION_ID_LIBRARY_VERSIONS ; 
 int /*<<< orphan*/  SHOW_LIB_VERSION (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SWRESAMPLE ; 
 int /*<<< orphan*/  SWSCALE ; 
 int /*<<< orphan*/  avcodec ; 
 int /*<<< orphan*/  avdevice ; 
 int /*<<< orphan*/  avfilter ; 
 int /*<<< orphan*/  avformat ; 
 int /*<<< orphan*/  avutil ; 
 int /*<<< orphan*/  postproc ; 
 int /*<<< orphan*/  swresample ; 
 int /*<<< orphan*/  swscale ; 
 int /*<<< orphan*/  writer_print_section_footer (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  writer_print_section_header (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ffprobe_show_library_versions(WriterContext *w)
{
    writer_print_section_header(w, SECTION_ID_LIBRARY_VERSIONS);
    SHOW_LIB_VERSION(avutil,     AVUTIL);
    SHOW_LIB_VERSION(avcodec,    AVCODEC);
    SHOW_LIB_VERSION(avformat,   AVFORMAT);
    SHOW_LIB_VERSION(avdevice,   AVDEVICE);
    SHOW_LIB_VERSION(avfilter,   AVFILTER);
    SHOW_LIB_VERSION(swscale,    SWSCALE);
    SHOW_LIB_VERSION(swresample, SWRESAMPLE);
    SHOW_LIB_VERSION(postproc,   POSTPROC);
    writer_print_section_footer(w);
}