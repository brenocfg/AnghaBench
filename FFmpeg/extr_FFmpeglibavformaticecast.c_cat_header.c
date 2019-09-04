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
typedef  int /*<<< orphan*/  AVBPrint ;

/* Variables and functions */
 scalar_t__ NOT_EMPTY (char const*) ; 
 int /*<<< orphan*/  av_bprintf (int /*<<< orphan*/ *,char*,char const*,char const*) ; 

__attribute__((used)) static void cat_header(AVBPrint *bp, const char key[], const char value[])
{
    if (NOT_EMPTY(value))
        av_bprintf(bp, "%s: %s\r\n", key, value);
}