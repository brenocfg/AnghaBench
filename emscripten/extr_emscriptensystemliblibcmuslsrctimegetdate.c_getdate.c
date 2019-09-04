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
struct tm {int dummy; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 scalar_t__ ENOMEM ; 
 int PTHREAD_CANCEL_DEFERRED ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 scalar_t__ fgets (char*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char*,char*) ; 
 int getdate_err ; 
 char* getenv (char*) ; 
 int /*<<< orphan*/  pthread_setcancelstate (int,int*) ; 
 char* strptime (char const*,char*,struct tm*) ; 

struct tm *getdate(const char *s)
{
	static struct tm tmbuf;
	struct tm *ret = 0;
	char *datemsk = getenv("DATEMSK");
	FILE *f = 0;
	char fmt[100], *p;
	int cs;

	pthread_setcancelstate(PTHREAD_CANCEL_DEFERRED, &cs);

	if (!datemsk) {
		getdate_err = 1;
		goto out;
	}

	f = fopen(datemsk, "rbe");
	if (!f) {
		if (errno == ENOMEM) getdate_err = 6;
		else getdate_err = 2;
		goto out;
	}

	while (fgets(fmt, sizeof fmt, f)) {
		p = strptime(s, fmt, &tmbuf);
		if (p && !*p) {
			ret = &tmbuf;
			goto out;
		}
	}

	getdate_err = 7;
out:
	if (f) fclose(f);
	pthread_setcancelstate(cs, 0);
	return ret;
}