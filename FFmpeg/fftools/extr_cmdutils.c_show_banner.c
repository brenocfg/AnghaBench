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
typedef  int /*<<< orphan*/  OptionDef ;

/* Variables and functions */
 int /*<<< orphan*/  AV_LOG_INFO ; 
 int INDENT ; 
 int SHOW_CONFIG ; 
 int SHOW_COPYRIGHT ; 
 int SHOW_VERSION ; 
 scalar_t__ hide_banner ; 
 int locate_option (int,char**,int /*<<< orphan*/  const*,char*) ; 
 int /*<<< orphan*/  print_all_libs_info (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  print_program_info (int,int /*<<< orphan*/ ) ; 

void show_banner(int argc, char **argv, const OptionDef *options)
{
    int idx = locate_option(argc, argv, options, "version");
    if (hide_banner || idx)
        return;

    print_program_info (INDENT|SHOW_COPYRIGHT, AV_LOG_INFO);
    print_all_libs_info(INDENT|SHOW_CONFIG,  AV_LOG_INFO);
    print_all_libs_info(INDENT|SHOW_VERSION, AV_LOG_INFO);
}