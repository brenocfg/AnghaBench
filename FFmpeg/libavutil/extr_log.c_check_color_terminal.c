#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int wAttributes; } ;
typedef  TYPE_1__ CONSOLE_SCREEN_BUFFER_INFO ;

/* Variables and functions */
 int /*<<< orphan*/  GetConsoleScreenBufferInfo (scalar_t__,TYPE_1__*) ; 
 scalar_t__ GetStdHandle (int /*<<< orphan*/ ) ; 
 scalar_t__ INVALID_HANDLE_VALUE ; 
 int /*<<< orphan*/  STD_ERROR_HANDLE ; 
 int attr_orig ; 
 int background ; 
 scalar_t__ con ; 
 char* getenv (char*) ; 
 scalar_t__ isatty (int) ; 
 scalar_t__ strstr (char*,char*) ; 
 int use_color ; 

__attribute__((used)) static void check_color_terminal(void)
{
#if defined(_WIN32) && HAVE_SETCONSOLETEXTATTRIBUTE
    CONSOLE_SCREEN_BUFFER_INFO con_info;
    con = GetStdHandle(STD_ERROR_HANDLE);
    use_color = (con != INVALID_HANDLE_VALUE) && !getenv("NO_COLOR") &&
                !getenv("AV_LOG_FORCE_NOCOLOR");
    if (use_color) {
        GetConsoleScreenBufferInfo(con, &con_info);
        attr_orig  = con_info.wAttributes;
        background = attr_orig & 0xF0;
    }
#elif HAVE_ISATTY
    char *term = getenv("TERM");
    use_color = !getenv("NO_COLOR") && !getenv("AV_LOG_FORCE_NOCOLOR") &&
                (getenv("TERM") && isatty(2) || getenv("AV_LOG_FORCE_COLOR"));
    if (   getenv("AV_LOG_FORCE_256COLOR")
        || (term && strstr(term, "256color")))
        use_color *= 256;
#else
    use_color = getenv("AV_LOG_FORCE_COLOR") && !getenv("NO_COLOR") &&
               !getenv("AV_LOG_FORCE_NOCOLOR");
#endif
}