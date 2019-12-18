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
struct strbuf {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  PATH_SEP ; 
 scalar_t__ is_absolute_path (char const*) ; 
 char const* make_nonrelative_path (char const*) ; 
 int /*<<< orphan*/  strbuf_addch (struct strbuf*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strbuf_addstr (struct strbuf*,char const*) ; 

__attribute__((used)) static void add_path(struct strbuf *out, const char *path)
{
	if (path && *path) {
		if (is_absolute_path(path))
			strbuf_addstr(out, path);
		else
			strbuf_addstr(out, make_nonrelative_path(path));

		strbuf_addch(out, PATH_SEP);
	}
}