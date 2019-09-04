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
 scalar_t__ av_isspace (char) ; 
 int /*<<< orphan*/  av_strlcpy (char*,char*,int) ; 
 int strlen (char*) ; 
 char* strstr (char*,char*) ; 

__attribute__((used)) static void choose_qop(char *qop, int size)
{
    char *ptr = strstr(qop, "auth");
    char *end = ptr + strlen("auth");

    if (ptr && (!*end || av_isspace(*end) || *end == ',') &&
        (ptr == qop || av_isspace(ptr[-1]) || ptr[-1] == ',')) {
        av_strlcpy(qop, "auth", size);
    } else {
        qop[0] = 0;
    }
}