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
 int RTLD_LOCAL ; 
 int RTLD_NOW ; 
 char* av_asprintf (char*,char const*,char const*) ; 
 int /*<<< orphan*/  av_free (char*) ; 
 void* dlopen (char*,int) ; 

__attribute__((used)) static void *try_load(const char *dir, const char *soname)
{
    char *path = av_asprintf("%s/%s.so", dir, soname);
    void *ret = NULL;

    if (path) {
        ret = dlopen(path, RTLD_LOCAL|RTLD_NOW);
        av_free(path);
    }

    return ret;
}