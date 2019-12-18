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
 int strtod (char*,int /*<<< orphan*/ *) ; 
 char* strtok (int /*<<< orphan*/ *,char*) ; 

__attribute__((used)) static double parse_hhmmss_strtok()
{
    /* Assumes strtok has already been called on a string.  Intends to parse
     * hh:mm:ss.ss or mm:ss.ss or ss.ss or ss into double seconds.  Actually
     * parses a list of doubles separated by colons, multiplying the current
     * result by 60 then adding in the next value.  Malformed input does not
     * result in a explicit error condition but instead returns an
     * intermediate result. */
    double duration = 0;
    char* str;
    while ((str = strtok(NULL, ":")) != NULL)
        duration = 60*duration + strtod(str, NULL);
    return duration;
}