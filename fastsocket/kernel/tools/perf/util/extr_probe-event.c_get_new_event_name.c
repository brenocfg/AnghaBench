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
struct strlist {int dummy; } ;

/* Variables and functions */
 int EEXIST ; 
 int ERANGE ; 
 int MAX_EVENT_INDEX ; 
 int e_snprintf (char*,size_t,char*,char const*,...) ; 
 int /*<<< orphan*/  pr_debug (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_warning (char*,...) ; 
 int /*<<< orphan*/  strerror (int) ; 
 int /*<<< orphan*/  strlist__has_entry (struct strlist*,char*) ; 

__attribute__((used)) static int get_new_event_name(char *buf, size_t len, const char *base,
			      struct strlist *namelist, bool allow_suffix)
{
	int i, ret;

	/* Try no suffix */
	ret = e_snprintf(buf, len, "%s", base);
	if (ret < 0) {
		pr_debug("snprintf() failed: %s\n", strerror(-ret));
		return ret;
	}
	if (!strlist__has_entry(namelist, buf))
		return 0;

	if (!allow_suffix) {
		pr_warning("Error: event \"%s\" already exists. "
			   "(Use -f to force duplicates.)\n", base);
		return -EEXIST;
	}

	/* Try to add suffix */
	for (i = 1; i < MAX_EVENT_INDEX; i++) {
		ret = e_snprintf(buf, len, "%s_%d", base, i);
		if (ret < 0) {
			pr_debug("snprintf() failed: %s\n", strerror(-ret));
			return ret;
		}
		if (!strlist__has_entry(namelist, buf))
			break;
	}
	if (i == MAX_EVENT_INDEX) {
		pr_warning("Too many events are on the same function.\n");
		ret = -ERANGE;
	}

	return ret;
}