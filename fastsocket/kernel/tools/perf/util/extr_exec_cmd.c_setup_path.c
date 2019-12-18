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
struct strbuf {int /*<<< orphan*/  buf; } ;

/* Variables and functions */
 struct strbuf STRBUF_INIT ; 
 int /*<<< orphan*/  add_path (struct strbuf*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  argv0_path ; 
 char* getenv (char*) ; 
 int /*<<< orphan*/  perf_exec_path () ; 
 int /*<<< orphan*/  setenv (char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  strbuf_addstr (struct strbuf*,char const*) ; 
 int /*<<< orphan*/  strbuf_release (struct strbuf*) ; 

void setup_path(void)
{
	const char *old_path = getenv("PATH");
	struct strbuf new_path = STRBUF_INIT;

	add_path(&new_path, perf_exec_path());
	add_path(&new_path, argv0_path);

	if (old_path)
		strbuf_addstr(&new_path, old_path);
	else
		strbuf_addstr(&new_path, "/usr/local/bin:/usr/bin:/bin");

	setenv("PATH", new_path.buf, 1);

	strbuf_release(&new_path);
}