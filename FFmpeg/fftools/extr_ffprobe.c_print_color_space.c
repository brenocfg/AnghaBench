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
typedef  enum AVColorSpace { ____Placeholder_AVColorSpace } AVColorSpace ;
typedef  int /*<<< orphan*/  WriterContext ;

/* Variables and functions */
 int AVCOL_SPC_UNSPECIFIED ; 
 char* av_color_space_name (int) ; 
 int /*<<< orphan*/  print_str (char*,char const*) ; 
 int /*<<< orphan*/  print_str_opt (char*,char*) ; 

__attribute__((used)) static void print_color_space(WriterContext *w, enum AVColorSpace color_space)
{
    const char *val = av_color_space_name(color_space);
    if (!val || color_space == AVCOL_SPC_UNSPECIFIED) {
        print_str_opt("color_space", "unknown");
    } else {
        print_str("color_space", val);
    }
}