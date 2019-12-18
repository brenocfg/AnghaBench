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
typedef  int /*<<< orphan*/  time_t ;
typedef  int /*<<< orphan*/  buf ;

/* Variables and functions */
 int BUFSIZ ; 
 char* bmake_strdup (char*) ; 
 int /*<<< orphan*/  gmtime (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  localtime (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strftime (char*,int,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  time (int /*<<< orphan*/ *) ; 

__attribute__((used)) static char *
VarStrftime(const char *fmt, int zulu, time_t utc)
{
    char buf[BUFSIZ];

    if (!utc)
	time(&utc);
    if (!*fmt)
	fmt = "%c";
    strftime(buf, sizeof(buf), fmt, zulu ? gmtime(&utc) : localtime(&utc));
    
    buf[sizeof(buf) - 1] = '\0';
    return bmake_strdup(buf);
}