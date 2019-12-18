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
 int /*<<< orphan*/  message5 (char const*,char const*,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
message (char const *format_msgid, char const *arg1, char const *arg2)
{
  message5 (format_msgid, arg1, arg2, 0, 0);
}