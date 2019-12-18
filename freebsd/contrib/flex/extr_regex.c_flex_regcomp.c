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
typedef  int /*<<< orphan*/  regex_t ;

/* Variables and functions */
 char* _ (char*) ; 
 scalar_t__ flex_alloc (int const) ; 
 int /*<<< orphan*/  flexfatal (char*) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int regcomp (int /*<<< orphan*/ *,char const*,int) ; 
 int /*<<< orphan*/  regerror (int,int /*<<< orphan*/ *,char*,int const) ; 
 int /*<<< orphan*/  snprintf (char*,int const,char*,char const*,char*) ; 

void flex_regcomp(regex_t *preg, const char *regex, int cflags)
{
    int err;

	memset (preg, 0, sizeof (regex_t));

	if ((err = regcomp (preg, regex, cflags)) != 0) {
        const int errbuf_sz = 200;
        char *errbuf, *rxerr;

		errbuf = (char*)flex_alloc(errbuf_sz *sizeof(char));
		if (!errbuf)
			flexfatal(_("Unable to allocate buffer to report regcomp"));
		rxerr = (char*)flex_alloc(errbuf_sz *sizeof(char));
		if (!rxerr)
			flexfatal(_("Unable to allocate buffer for regerror"));
		regerror (err, preg, rxerr, errbuf_sz);
		snprintf (errbuf, errbuf_sz, "regcomp for \"%s\" failed: %s", regex, rxerr);

		flexfatal (errbuf);
        free(errbuf);
        free(rxerr);
	}
}