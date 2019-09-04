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
 long LONG_MIN ; 
 int /*<<< orphan*/  free (char*) ; 
 char* getInfoField (char*,char*) ; 
 long strtol (char*,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static long getLongInfoField(char *info, char *field) {
    char *value = getInfoField(info,field);
    long l;

    if (!value) return LONG_MIN;
    l = strtol(value,NULL,10);
    free(value);
    return l;
}