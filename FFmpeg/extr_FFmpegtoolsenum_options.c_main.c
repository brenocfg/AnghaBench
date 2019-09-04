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

/* Variables and functions */
 int /*<<< orphan*/  print_usage () ; 
 int /*<<< orphan*/  show_codec_opts () ; 
 int /*<<< orphan*/  show_format_opts () ; 
 int /*<<< orphan*/  strcmp (char*,char*) ; 

int main(int argc, char **argv)
{
    if (argc < 2)
        print_usage();

    if (!strcmp(argv[1], "format"))
        show_format_opts();
    else if (!strcmp(argv[1], "codec"))
        show_codec_opts();
    else
        print_usage();

    return 0;
}