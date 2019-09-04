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
struct tm {int tm_hour; int tm_min; int tm_sec; } ;
struct timeval {scalar_t__ tv_usec; scalar_t__ tv_sec; } ;
struct input {int num; } ;
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
 int /*<<< orphan*/  dump (char const*,int,unsigned char*,size_t,int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*,int,char*) ; 
 int /*<<< orphan*/  gettimeofday (struct timeval*,int /*<<< orphan*/ *) ; 
 struct tm* localtime (scalar_t__*) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,int,int,int,long) ; 
 int /*<<< orphan*/  stderr ; 
 scalar_t__ time (int /*<<< orphan*/ *) ; 

__attribute__((used)) static
int my_trace(CURL *handle, curl_infotype type,
             char *data, size_t size,
             void *userp)
{
  char timebuf[60];
  const char *text;
  struct input *i = (struct input *)userp;
  int num = i->num;
  static time_t epoch_offset;
  static int    known_offset;
  struct timeval tv;
  time_t secs;
  struct tm *now;
  (void)handle; /* prevent compiler warning */

  gettimeofday(&tv, NULL);
  if(!known_offset) {
    epoch_offset = time(NULL) - tv.tv_sec;
    known_offset = 1;
  }
  secs = epoch_offset + tv.tv_sec;
  now = localtime(&secs);  /* not thread safe but we don't care */
  snprintf(timebuf, sizeof(timebuf), "%02d:%02d:%02d.%06ld",
           now->tm_hour, now->tm_min, now->tm_sec, (long)tv.tv_usec);

  switch(type) {
  case CURLINFO_TEXT:
    fprintf(stderr, "%s [%d] Info: %s", timebuf, num, data);
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

  dump(text, num, (unsigned char *)data, size, 1);
  return 0;
}