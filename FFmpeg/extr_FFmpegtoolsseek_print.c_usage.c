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
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  stdout ; 

__attribute__((used)) static void usage(int ret)
{
    fprintf(ret ? stderr : stdout,
            "Usage: seek_print file [command ...]\n"
            "Commands:\n"
            "    read\n"
            "    seek:stream:min_ts:ts:max_ts:flags\n"
            );
    exit(ret);
}