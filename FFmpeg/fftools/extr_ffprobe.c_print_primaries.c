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
typedef  enum AVColorPrimaries { ____Placeholder_AVColorPrimaries } AVColorPrimaries ;
typedef  int /*<<< orphan*/  WriterContext ;

/* Variables and functions */
 int AVCOL_PRI_UNSPECIFIED ; 
 char* av_color_primaries_name (int) ; 
 int /*<<< orphan*/  print_str (char*,char const*) ; 
 int /*<<< orphan*/  print_str_opt (char*,char*) ; 

__attribute__((used)) static void print_primaries(WriterContext *w, enum AVColorPrimaries color_primaries)
{
    const char *val = av_color_primaries_name(color_primaries);
    if (!val || color_primaries == AVCOL_PRI_UNSPECIFIED) {
        print_str_opt("color_primaries", "unknown");
    } else {
        print_str("color_primaries", val);
    }
}