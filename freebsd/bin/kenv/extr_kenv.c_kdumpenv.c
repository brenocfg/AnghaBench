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
 int /*<<< orphan*/  KENV_DUMP ; 
 scalar_t__ Nflag ; 
 char* calloc (int,int) ; 
 int /*<<< orphan*/  free (char*) ; 
 scalar_t__ hflag ; 
 int kenv (int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  printf (char*,char*,...) ; 
 char* strchr (char*,char) ; 
 scalar_t__ strlen (char*) ; 
 scalar_t__ strncmp (char*,char*,int) ; 

__attribute__((used)) static int
kdumpenv(void)
{
	char *buf, *bp, *cp;
	int buflen, envlen;

	envlen = kenv(KENV_DUMP, NULL, NULL, 0);
	if (envlen < 0)
		return (-1);
	for (;;) {
		buflen = envlen * 120 / 100;
		buf = calloc(1, buflen + 1);
		if (buf == NULL)
			return (-1);
		envlen = kenv(KENV_DUMP, NULL, buf, buflen);
		if (envlen < 0) {
			free(buf);
			return (-1);
		}
		if (envlen > buflen)
			free(buf);
		else
			break;
	}

	for (bp = buf; *bp != '\0'; bp += strlen(bp) + 1) {
		if (hflag) {
			if (strncmp(bp, "hint.", 5) != 0)
				continue;
		}
		cp = strchr(bp, '=');
		if (cp == NULL)
			continue;
		*cp++ = '\0';
		if (Nflag)
			printf("%s\n", bp);
		else
			printf("%s=\"%s\"\n", bp, cp);
		bp = cp;
	}

	free(buf);
	return (0);
}