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
struct timeval {int dummy; } ;
struct ProgressData {scalar_t__ initial_size; scalar_t__ prev; int width; struct timeval prevtime; int /*<<< orphan*/  out; scalar_t__ calls; } ;
typedef  int /*<<< orphan*/  format ;
typedef  scalar_t__ curl_off_t ;

/* Variables and functions */
 scalar_t__ CURL_OFF_T_MAX ; 
 int MAX_BARLENGTH ; 
 int /*<<< orphan*/  fflush (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fly (struct ProgressData*,int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*,double) ; 
 int /*<<< orphan*/  memset (char*,char,int) ; 
 int /*<<< orphan*/  msnprintf (char*,int,char*,int) ; 
 long tvdiff (struct timeval,struct timeval) ; 
 struct timeval tvnow () ; 

int tool_progress_cb(void *clientp,
                     curl_off_t dltotal, curl_off_t dlnow,
                     curl_off_t ultotal, curl_off_t ulnow)
{
  /* The original progress-bar source code was written for curl by Lars Aas,
     and this new edition inherits some of his concepts. */

  struct timeval now = tvnow();
  struct ProgressData *bar = (struct ProgressData *)clientp;
  curl_off_t total;
  curl_off_t point;

  /* Calculate expected transfer size. initial_size can be less than zero
     when indicating that we are expecting to get the filesize from the
     remote */
  if(bar->initial_size < 0 ||
     ((CURL_OFF_T_MAX - bar->initial_size) < (dltotal + ultotal)))
    total = CURL_OFF_T_MAX;
  else
    total = dltotal + ultotal + bar->initial_size;

  /* Calculate the current progress. initial_size can be less than zero when
     indicating that we are expecting to get the filesize from the remote */
  if(bar->initial_size < 0 ||
     ((CURL_OFF_T_MAX - bar->initial_size) < (dlnow + ulnow)))
    point = CURL_OFF_T_MAX;
  else
    point = dlnow + ulnow + bar->initial_size;

  if(bar->calls) {
    /* after first call... */
    if(total) {
      /* we know the total data to get... */
      if(bar->prev == point)
        /* progress didn't change since last invoke */
        return 0;
      else if((tvdiff(now, bar->prevtime) < 100L) && point < total)
        /* limit progress-bar updating to 10 Hz except when we're at 100% */
        return 0;
    }
    else {
      /* total is unknown */
      if(tvdiff(now, bar->prevtime) < 100L)
        /* limit progress-bar updating to 10 Hz */
        return 0;
      fly(bar, point != bar->prev);
    }
  }

  /* simply count invokes */
  bar->calls++;

  if((total > 0) && (point != bar->prev)) {
    char line[MAX_BARLENGTH + 1];
    char format[40];
    double frac;
    double percent;
    int barwidth;
    int num;
    if(point > total)
      /* we have got more than the expected total! */
      total = point;

    frac = (double)point / (double)total;
    percent = frac * 100.0;
    barwidth = bar->width - 7;
    num = (int) (((double)barwidth) * frac);
    if(num > MAX_BARLENGTH)
      num = MAX_BARLENGTH;
    memset(line, '#', num);
    line[num] = '\0';
    msnprintf(format, sizeof(format), "\r%%-%ds %%5.1f%%%%", barwidth);
    fprintf(bar->out, format, line, percent);
  }
  fflush(bar->out);
  bar->prev = point;
  bar->prevtime = now;

  return 0;
}