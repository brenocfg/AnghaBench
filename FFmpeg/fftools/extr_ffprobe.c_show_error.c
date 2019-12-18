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
typedef  int /*<<< orphan*/  errbuf ;
typedef  int /*<<< orphan*/  WriterContext ;

/* Variables and functions */
 int /*<<< orphan*/  AVUNERROR (int) ; 
 int /*<<< orphan*/  SECTION_ID_ERROR ; 
 scalar_t__ av_strerror (int,char*,int) ; 
 int /*<<< orphan*/  print_int (char*,int) ; 
 int /*<<< orphan*/  print_str (char*,char const*) ; 
 char* strerror (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  writer_print_section_footer (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  writer_print_section_header (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void show_error(WriterContext *w, int err)
{
    char errbuf[128];
    const char *errbuf_ptr = errbuf;

    if (av_strerror(err, errbuf, sizeof(errbuf)) < 0)
        errbuf_ptr = strerror(AVUNERROR(err));

    writer_print_section_header(w, SECTION_ID_ERROR);
    print_int("code", err);
    print_str("string", errbuf_ptr);
    writer_print_section_footer(w);
}