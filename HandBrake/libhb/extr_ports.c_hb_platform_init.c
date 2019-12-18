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
 int /*<<< orphan*/  _IONBF ; 
 int /*<<< orphan*/  hb_error (char*) ; 
 int /*<<< orphan*/  init_cpu_info () ; 
 int /*<<< orphan*/  pthread_win32_process_attach_np () ; 
 int setvbuf (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  stdout ; 

int hb_platform_init()
{
    int result = 0;

#if defined(SYS_MINGW) && defined(PTW32_VERSION)
    result = !pthread_win32_process_attach_np();
    if (result)
    {
        hb_error("pthread_win32_process_attach_np() failed!");
        return -1;
    }
#endif

#if defined(_WIN32) || defined(__MINGW32__)
    /*
     * win32 _IOLBF (line-buffering) is the same as _IOFBF (full-buffering).
     * force it to unbuffered otherwise informative output is not easily parsed.
     */
    result = setvbuf(stdout, NULL, _IONBF, 0);
    if (result)
    {
        hb_error("setvbuf(stdout, NULL, _IONBF, 0) failed!");
        return -1;
    }
    result = setvbuf(stderr, NULL, _IONBF, 0);
    if (result)
    {
        hb_error("setvbuf(stderr, NULL, _IONBF, 0) failed!");
        return -1;
    }
#endif

    init_cpu_info();

    return result;
}