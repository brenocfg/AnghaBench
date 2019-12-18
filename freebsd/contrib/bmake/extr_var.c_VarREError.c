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
 int /*<<< orphan*/  Error (char*,char const*,char*) ; 
 char* bmake_malloc (int) ; 
 int /*<<< orphan*/  free (char*) ; 
 int regerror (int,int /*<<< orphan*/ *,char*,int) ; 

__attribute__((used)) static void
VarREError(int reerr, regex_t *pat, const char *str)
{
    char *errbuf;
    int errlen;

    errlen = regerror(reerr, pat, 0, 0);
    errbuf = bmake_malloc(errlen);
    regerror(reerr, pat, errbuf, errlen);
    Error("%s: %s", str, errbuf);
    free(errbuf);
}