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
 int /*<<< orphan*/  HOOK_MALLOC_FAILED ; 
 char* malloc (scalar_t__) ; 
 int /*<<< orphan*/  sprintf (char*,char*,...) ; 
 int /*<<< orphan*/  strcpy (char*,char*) ; 
 scalar_t__ strlen (char*) ; 
 char* strrchr (char*,char) ; 
 int strtol (char*,char**,int) ; 

__attribute__((used)) static char * _mdns_mangle_name(char* in) {
    char *p = strrchr(in, '-');
    int suffix = 0;
    if (p == NULL) {
        //No - in ``in``
        suffix = 2;
    } else {
        char *endp = NULL;
        suffix = strtol(p + 1, &endp, 10);
        if (*endp != 0) {
            //suffix is not numerical
            suffix = 2;
            p = NULL; //so we append -suffix to the entire string
        }
    }
    char *ret;
    if (p == NULL) {
        //need to add -2 to string
        ret = malloc(strlen(in) + 3);
        if (ret == NULL) {
            HOOK_MALLOC_FAILED;
            return NULL;
        }
        sprintf(ret, "%s-2", in);
    } else {
        ret = malloc(strlen(in) + 2); //one extra byte in case 9-10 or 99-100 etc
        if (ret == NULL) {
            HOOK_MALLOC_FAILED;
            return NULL;
        }
        strcpy(ret, in);
        int baseLen = p - in; //length of 'bla' in 'bla-123'
        //overwrite suffix with new suffix
        sprintf(ret + baseLen, "-%d", suffix + 1);
    }
    return ret;
}