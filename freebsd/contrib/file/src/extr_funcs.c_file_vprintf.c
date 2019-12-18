#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  va_list ;
struct TYPE_2__ {char* buf; } ;
struct magic_set {int event_flags; TYPE_1__ o; } ;

/* Variables and functions */
 int EVENT_HAD_ERR ; 
 int asprintf (char**,char*,char*,char*) ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  stderr ; 
 char* strerror (int /*<<< orphan*/ ) ; 
 int vasprintf (char**,char const*,int /*<<< orphan*/ ) ; 

int
file_vprintf(struct magic_set *ms, const char *fmt, va_list ap)
{
	int len;
	char *buf, *newstr;

	if (ms->event_flags & EVENT_HAD_ERR)
		return 0;
	len = vasprintf(&buf, fmt, ap);
	if (len < 0)
		goto out;

	if (ms->o.buf != NULL) {
		len = asprintf(&newstr, "%s%s", ms->o.buf, buf);
		free(buf);
		if (len < 0)
			goto out;
		free(ms->o.buf);
		buf = newstr;
	}
	ms->o.buf = buf;
	return 0;
out:
	fprintf(stderr, "vasprintf failed (%s)", strerror(errno));
	return -1;
}