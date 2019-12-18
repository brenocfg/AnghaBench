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
typedef  int /*<<< orphan*/  FARPROC ;

/* Variables and functions */
 int /*<<< orphan*/  GetProcAddress (void*,char const*) ; 
 void* dlsym (void*,char const*) ; 

void * hb_dlsym(void *h, const char *name)
{
#ifdef SYS_MINGW
    FARPROC p = GetProcAddress(h, name);
#else
    void *p = dlsym(h, name);
#endif
    return p;
}