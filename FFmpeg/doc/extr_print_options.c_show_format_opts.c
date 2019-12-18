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
 int /*<<< orphan*/  avformat_options ; 
 int /*<<< orphan*/  printf (char*) ; 
 int /*<<< orphan*/  show_opts (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void show_format_opts(void)
{
    printf("@section Format AVOptions\n");
    show_opts(avformat_options, 0);
}