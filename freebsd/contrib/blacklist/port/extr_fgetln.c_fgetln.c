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
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 size_t BUFSIZ ; 
 int errno ; 
 int /*<<< orphan*/ * fgets (char*,size_t,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (char*) ; 
 char* malloc (size_t) ; 
 char* realloc (char*,size_t) ; 
 char* strchr (char*,char) ; 
 size_t strlen (char*) ; 

char *
fgetln(FILE *fp, size_t *len)
{
	static char *buf = NULL;
	static size_t bufsiz = 0;
	char *ptr;


	if (buf == NULL) {
		bufsiz = BUFSIZ;
		if ((buf = malloc(bufsiz)) == NULL)
			return NULL;
	}

	if (fgets(buf, bufsiz, fp) == NULL)
		return NULL;

	*len = 0;
	while ((ptr = strchr(&buf[*len], '\n')) == NULL) {
		size_t nbufsiz = bufsiz + BUFSIZ;
		char *nbuf = realloc(buf, nbufsiz);

		if (nbuf == NULL) {
			int oerrno = errno;
			free(buf);
			errno = oerrno;
			buf = NULL;
			return NULL;
		} else
			buf = nbuf;

		if (fgets(&buf[bufsiz], BUFSIZ, fp) == NULL) {
			buf[bufsiz] = '\0';
			*len = strlen(buf);
			return buf;
		}

		*len = bufsiz;
		bufsiz = nbufsiz;
	}

	*len = (ptr - buf) + 1;
	return buf;
}