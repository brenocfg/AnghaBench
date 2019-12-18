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
struct strbuf {int len; int /*<<< orphan*/  buf; } ;
struct dirent {char const* d_name; } ;
struct cmdnames {int dummy; } ;
typedef  int /*<<< orphan*/  DIR ;

/* Variables and functions */
 struct strbuf STRBUF_INIT ; 
 int /*<<< orphan*/  add_cmdname (struct cmdnames*,char const*,int) ; 
 int /*<<< orphan*/  closedir (int /*<<< orphan*/ *) ; 
 scalar_t__ has_extension (char const*,char*) ; 
 int /*<<< orphan*/  is_executable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * opendir (char const*) ; 
 scalar_t__ prefixcmp (char const*,char const*) ; 
 struct dirent* readdir (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strbuf_addf (struct strbuf*,char*,char const*) ; 
 int /*<<< orphan*/  strbuf_addstr (struct strbuf*,char const*) ; 
 int /*<<< orphan*/  strbuf_release (struct strbuf*) ; 
 int /*<<< orphan*/  strbuf_setlen (struct strbuf*,int) ; 
 int strlen (char const*) ; 

__attribute__((used)) static void list_commands_in_dir(struct cmdnames *cmds,
					 const char *path,
					 const char *prefix)
{
	int prefix_len;
	DIR *dir = opendir(path);
	struct dirent *de;
	struct strbuf buf = STRBUF_INIT;
	int len;

	if (!dir)
		return;
	if (!prefix)
		prefix = "perf-";
	prefix_len = strlen(prefix);

	strbuf_addf(&buf, "%s/", path);
	len = buf.len;

	while ((de = readdir(dir)) != NULL) {
		int entlen;

		if (prefixcmp(de->d_name, prefix))
			continue;

		strbuf_setlen(&buf, len);
		strbuf_addstr(&buf, de->d_name);
		if (!is_executable(buf.buf))
			continue;

		entlen = strlen(de->d_name) - prefix_len;
		if (has_extension(de->d_name, ".exe"))
			entlen -= 4;

		add_cmdname(cmds, de->d_name + prefix_len, entlen);
	}
	closedir(dir);
	strbuf_release(&buf);
}