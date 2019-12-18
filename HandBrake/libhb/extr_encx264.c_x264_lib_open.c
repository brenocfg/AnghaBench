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
 int /*<<< orphan*/  HB_SO_EXT ; 
 int /*<<< orphan*/  free (char*) ; 
 void* hb_dlopen (char*) ; 
 char* hb_strdup_printf (char*,char const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void * x264_lib_open(const char *names[])
{
    if (names == NULL)
        return NULL;

    void *h;
    int   ii = 0;
    while (names[ii] != NULL)
    {
        char *name = hb_strdup_printf("%s%s", names[ii], HB_SO_EXT);
        h = hb_dlopen(name);
        free(name);
        if (h != NULL)
        {
            return h;
        }
        ii++;
    }
    return NULL;
}