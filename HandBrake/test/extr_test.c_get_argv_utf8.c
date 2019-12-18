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
typedef  int /*<<< orphan*/  wchar_t ;

/* Variables and functions */
 int /*<<< orphan*/  CP_UTF8 ; 
 int /*<<< orphan*/ ** CommandLineToArgvW (int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  GetCommandLineW () ; 
 int /*<<< orphan*/  LocalFree (int /*<<< orphan*/ **) ; 
 scalar_t__ WideCharToMultiByte (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,char*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 char** malloc (int) ; 

__attribute__((used)) static int get_argv_utf8(int *argc_ptr, char ***argv_ptr)
{
#if defined( __MINGW32__ )
    int ret = 0;
    int argc;
    char **argv;

    wchar_t **argv_utf16 = CommandLineToArgvW(GetCommandLineW(), &argc);
    if (argv_utf16)
    {
        int i;
        int offset = (argc+1) * sizeof(char*);
        int size = offset;

        for(i = 0; i < argc; i++)
            size += WideCharToMultiByte(CP_UTF8, 0, argv_utf16[i], -1, NULL, 0, NULL, NULL );

        argv = malloc(size);
        if (argv != NULL)
        {
            for (i = 0; i < argc; i++)
            {
                argv[i] = (char*)argv + offset;
                offset += WideCharToMultiByte(CP_UTF8, 0, argv_utf16[i], -1, argv[i], size-offset, NULL, NULL);
            }
            argv[argc] = NULL;
            ret = 1;
        }
        LocalFree(argv_utf16);
    }
    if (ret)
    {
        *argc_ptr = argc;
        *argv_ptr = argv;
    }
    return ret;
#else
    // On other systems, assume command line is already utf8
    return 1;
#endif
}