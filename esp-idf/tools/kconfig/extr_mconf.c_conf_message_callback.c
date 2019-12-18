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
typedef  int /*<<< orphan*/  va_list ;
typedef  int /*<<< orphan*/  buf ;

/* Variables and functions */
 int /*<<< orphan*/  PATH_MAX ; 
 int /*<<< orphan*/  printf (char*,char*) ; 
 scalar_t__ save_and_exit ; 
 int /*<<< orphan*/  show_textbox (int /*<<< orphan*/ *,char*,int,int) ; 
 int /*<<< orphan*/  silent ; 
 int /*<<< orphan*/  vsnprintf (char*,int,char const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void conf_message_callback(const char *fmt, va_list ap)
{
	char buf[PATH_MAX+1];

	vsnprintf(buf, sizeof(buf), fmt, ap);
	if (save_and_exit) {
		if (!silent)
			printf("%s", buf);
	} else {
		show_textbox(NULL, buf, 6, 60);
	}
}