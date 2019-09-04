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
typedef  int /*<<< orphan*/  AVBPrint ;

/* Variables and functions */
 int /*<<< orphan*/  AV_BPRINT_SIZE_UNLIMITED ; 
 int /*<<< orphan*/  CC_IDENT ; 
 int /*<<< orphan*/  CONFIG_THIS_YEAR ; 
 int /*<<< orphan*/  FFMPEG_CONFIGURATION ; 
 int /*<<< orphan*/  FFMPEG_VERSION ; 
 int /*<<< orphan*/  SECTION_ID_PROGRAM_VERSION ; 
 int /*<<< orphan*/  av_bprint_finalize (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  av_bprint_init (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  print_fmt (char*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  print_str (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  program_birth_year ; 
 int /*<<< orphan*/  writer_print_section_footer (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  writer_print_section_header (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ffprobe_show_program_version(WriterContext *w)
{
    AVBPrint pbuf;
    av_bprint_init(&pbuf, 1, AV_BPRINT_SIZE_UNLIMITED);

    writer_print_section_header(w, SECTION_ID_PROGRAM_VERSION);
    print_str("version", FFMPEG_VERSION);
    print_fmt("copyright", "Copyright (c) %d-%d the FFmpeg developers",
              program_birth_year, CONFIG_THIS_YEAR);
    print_str("compiler_ident", CC_IDENT);
    print_str("configuration", FFMPEG_CONFIGURATION);
    writer_print_section_footer(w);

    av_bprint_finalize(&pbuf, NULL);
}