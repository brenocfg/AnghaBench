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
 char* strchr (char*,char) ; 

__attribute__((used)) static __inline__ char *
find_colon(char * str)
{
    char * start = str;
    char * colon;
    
    while ((colon = strchr(start, ':')) != NULL) {
	char * dst;
	char * src;

	if (colon == start) {
	    break;
	}
	if (colon[-1] != '\\')
	    break;
	for (dst = colon - 1, src = colon; *dst != '\0'; dst++, src++) {
	    *dst = *src;
	}
	start = colon;
    }
    return (colon);
}