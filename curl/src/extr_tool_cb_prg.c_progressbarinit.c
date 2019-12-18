#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct winsize {int ts_cols; int ws_col; } ;
struct ttysize {int ts_cols; int ws_col; } ;
struct ProgressData {int width; int tick; int barmove; int /*<<< orphan*/  out; int /*<<< orphan*/  initial_size; } ;
struct OperationConfig {TYPE_2__* global; int /*<<< orphan*/  resume_from; scalar_t__ use_resume; } ;
struct TYPE_5__ {scalar_t__ Left; scalar_t__ Right; } ;
struct TYPE_7__ {TYPE_1__ srWindow; } ;
struct TYPE_6__ {int /*<<< orphan*/  errors; } ;
typedef  scalar_t__ HANDLE ;
typedef  TYPE_3__ CONSOLE_SCREEN_BUFFER_INFO ;

/* Variables and functions */
 scalar_t__ GetConsoleScreenBufferInfo (scalar_t__,TYPE_3__*) ; 
 scalar_t__ GetStdHandle (int /*<<< orphan*/ ) ; 
 scalar_t__ INVALID_HANDLE_VALUE ; 
 int MAX_BARLENGTH ; 
 int /*<<< orphan*/  STDIN_FILENO ; 
 int /*<<< orphan*/  STD_ERROR_HANDLE ; 
 int /*<<< orphan*/  TIOCGSIZE ; 
 int /*<<< orphan*/  TIOCGWINSZ ; 
 int /*<<< orphan*/  curl_free (char*) ; 
 char* curlx_getenv (char*) ; 
 int /*<<< orphan*/  ioctl (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct winsize*) ; 
 int /*<<< orphan*/  memset (struct ProgressData*,int /*<<< orphan*/ ,int) ; 
 int strlen (char*) ; 
 long strtol (char*,char**,int) ; 

void progressbarinit(struct ProgressData *bar,
                     struct OperationConfig *config)
{
  char *colp;
  memset(bar, 0, sizeof(struct ProgressData));

  /* pass this through to progress function so
   * it can display progress towards total file
   * not just the part that's left. (21-may-03, dbyron) */
  if(config->use_resume)
    bar->initial_size = config->resume_from;

  colp = curlx_getenv("COLUMNS");
  if(colp) {
    char *endptr;
    long num = strtol(colp, &endptr, 10);
    if((endptr != colp) && (endptr == colp + strlen(colp)) && (num > 20) &&
       (num < 10000))
      bar->width = (int)num;
    curl_free(colp);
  }

  if(!bar->width) {
    int cols = 0;

#ifdef TIOCGSIZE
    struct ttysize ts;
    if(!ioctl(STDIN_FILENO, TIOCGSIZE, &ts))
      cols = ts.ts_cols;
#elif defined(TIOCGWINSZ)
    struct winsize ts;
    if(!ioctl(STDIN_FILENO, TIOCGWINSZ, &ts))
      cols = ts.ws_col;
#elif defined(WIN32)
    {
      HANDLE  stderr_hnd = GetStdHandle(STD_ERROR_HANDLE);
      CONSOLE_SCREEN_BUFFER_INFO console_info;

      if((stderr_hnd != INVALID_HANDLE_VALUE) &&
         GetConsoleScreenBufferInfo(stderr_hnd, &console_info)) {
        /*
         * Do not use +1 to get the true screen-width since writing a
         * character at the right edge will cause a line wrap.
         */
        cols = (int)
          (console_info.srWindow.Right - console_info.srWindow.Left);
      }
    }
#endif /* TIOCGSIZE */
    bar->width = cols;
  }

  if(!bar->width)
    bar->width = 79;
  else if(bar->width > MAX_BARLENGTH)
    bar->width = MAX_BARLENGTH;

  bar->out = config->global->errors;
  bar->tick = 150;
  bar->barmove = 1;
}