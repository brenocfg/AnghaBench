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
typedef  int /*<<< orphan*/  line ;
typedef  int /*<<< orphan*/  int32_t ;
typedef  int /*<<< orphan*/  AVIOContext ;

/* Variables and functions */
 int RPL_LINE_LENGTH ; 
 int /*<<< orphan*/  read_int (char*,char const**,int*) ; 
 int read_line (int /*<<< orphan*/ *,char*,int) ; 

__attribute__((used)) static int32_t read_line_and_int(AVIOContext * pb, int* error)
{
    char line[RPL_LINE_LENGTH];
    const char *endptr;
    *error |= read_line(pb, line, sizeof(line));
    return read_int(line, &endptr, error);
}