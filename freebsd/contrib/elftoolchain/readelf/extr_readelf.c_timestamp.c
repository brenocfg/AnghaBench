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
typedef  int /*<<< orphan*/  ts ;
typedef  int /*<<< orphan*/  time_t ;
struct tm {int tm_year; int tm_mon; int tm_mday; int tm_hour; int tm_min; int tm_sec; } ;

/* Variables and functions */
 struct tm* gmtime (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,int,int,int,int,int,int) ; 

__attribute__((used)) static char *
timestamp(time_t ti)
{
	static char ts[32];
	struct tm *t;

	t = gmtime(&ti);
	snprintf(ts, sizeof(ts), "%04d-%02d-%02dT%02d:%02d:%02d",
	    t->tm_year + 1900, t->tm_mon + 1, t->tm_mday, t->tm_hour,
	    t->tm_min, t->tm_sec);

	return (ts);
}