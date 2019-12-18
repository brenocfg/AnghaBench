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
typedef  int /*<<< orphan*/  timebuf ;
typedef  scalar_t__ time_t ;
struct tm {int /*<<< orphan*/  tm_sec; int /*<<< orphan*/  tm_min; int /*<<< orphan*/  tm_hour; } ;
struct timeval {scalar_t__ tv_usec; scalar_t__ tv_sec; } ;
struct libtest_trace_cfg {int /*<<< orphan*/  nohex; scalar_t__ tracetime; } ;
typedef  int curl_infotype ;
typedef  int /*<<< orphan*/  CURL ;

/* Variables and functions */
#define  CURLINFO_DATA_IN 134 
#define  CURLINFO_DATA_OUT 133 
#define  CURLINFO_HEADER_IN 132 
#define  CURLINFO_HEADER_OUT 131 
#define  CURLINFO_SSL_DATA_IN 130 
#define  CURLINFO_SSL_DATA_OUT 129 
#define  CURLINFO_TEXT 128 
 scalar_t__ epoch_offset ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*,char*) ; 
 int known_offset ; 
 int /*<<< orphan*/  libtest_debug_dump (char*,char const*,int /*<<< orphan*/ ,unsigned char*,size_t,int /*<<< orphan*/ ) ; 
 struct tm* localtime (scalar_t__*) ; 
 int /*<<< orphan*/  msnprintf (char*,int,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,long) ; 
 int /*<<< orphan*/  stderr ; 
 scalar_t__ time (int /*<<< orphan*/ *) ; 
 struct timeval tutil_tvnow () ; 

int libtest_debug_cb(CURL *handle, curl_infotype type,
                     unsigned char *data, size_t size,
                     void *userp)
{

  struct libtest_trace_cfg *trace_cfg = userp;
  const char *text;
  struct timeval tv;
  char timebuf[20];
  char *timestr;
  time_t secs;

  (void)handle;

  timebuf[0] = '\0';
  timestr = &timebuf[0];

  if(trace_cfg->tracetime) {
    struct tm *now;
    tv = tutil_tvnow();
    if(!known_offset) {
      epoch_offset = time(NULL) - tv.tv_sec;
      known_offset = 1;
    }
    secs = epoch_offset + tv.tv_sec;
    now = localtime(&secs);  /* not thread safe but we don't care */
    msnprintf(timebuf, sizeof(timebuf), "%02d:%02d:%02d.%06ld ",
              now->tm_hour, now->tm_min, now->tm_sec, (long)tv.tv_usec);
  }

  switch(type) {
  case CURLINFO_TEXT:
    fprintf(stderr, "%s== Info: %s", timestr, (char *)data);
    /* FALLTHROUGH */
  default: /* in case a new one is introduced to shock us */
    return 0;

  case CURLINFO_HEADER_OUT:
    text = "=> Send header";
    break;
  case CURLINFO_DATA_OUT:
    text = "=> Send data";
    break;
  case CURLINFO_SSL_DATA_OUT:
    text = "=> Send SSL data";
    break;
  case CURLINFO_HEADER_IN:
    text = "<= Recv header";
    break;
  case CURLINFO_DATA_IN:
    text = "<= Recv data";
    break;
  case CURLINFO_SSL_DATA_IN:
    text = "<= Recv SSL data";
    break;
  }

  libtest_debug_dump(timebuf, text, stderr, data, size, trace_cfg->nohex);
  return 0;
}