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
typedef  int /*<<< orphan*/  va_list ;
struct bsdar {char* progname; } ;

/* Variables and functions */
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  stderr ; 
 char* strerror (int) ; 
 int /*<<< orphan*/  vfprintf (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
bsdar_vwarnc(struct bsdar *bsdar, int code, const char *fmt, va_list ap)
{

	fprintf(stderr, "%s: warning: ", bsdar->progname);
	vfprintf(stderr, fmt, ap);
	if (code != 0)
		fprintf(stderr, ": %s", strerror(code));
	fprintf(stderr, "\n");
}