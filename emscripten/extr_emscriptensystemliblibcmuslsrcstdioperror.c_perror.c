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
 int /*<<< orphan*/  FLOCK (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FUNLOCK (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  fputc (char,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fwrite (char const*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * stderr ; 
 char* strerror (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strlen (char const*) ; 

void perror(const char *msg)
{
	FILE *f = stderr;
	char *errstr = strerror(errno);

	FLOCK(f);
	
	if (msg && *msg) {
		fwrite(msg, strlen(msg), 1, f);
		fputc(':', f);
		fputc(' ', f);
	}
	fwrite(errstr, strlen(errstr), 1, f);
	fputc('\n', f);

	FUNLOCK(f);
}