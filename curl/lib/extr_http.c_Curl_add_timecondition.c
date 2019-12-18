#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct tm {int tm_wday; size_t tm_mon; int /*<<< orphan*/  tm_sec; int /*<<< orphan*/  tm_min; int /*<<< orphan*/  tm_hour; scalar_t__ tm_year; int /*<<< orphan*/  tm_mday; } ;
struct connectdata {struct Curl_easy* data; } ;
struct TYPE_2__ {int timecondition; int /*<<< orphan*/  timevalue; } ;
struct Curl_easy {TYPE_1__ set; } ;
typedef  int /*<<< orphan*/  datestr ;
typedef  int /*<<< orphan*/  Curl_send_buffer ;
typedef  scalar_t__ CURLcode ;

/* Variables and functions */
 scalar_t__ CURLE_BAD_FUNCTION_ARGUMENT ; 
 scalar_t__ CURLE_OK ; 
#define  CURL_TIMECOND_IFMODSINCE 130 
#define  CURL_TIMECOND_IFUNMODSINCE 129 
#define  CURL_TIMECOND_LASTMOD 128 
 int CURL_TIMECOND_NONE ; 
 scalar_t__ Curl_add_buffer (int /*<<< orphan*/ **,char*,int /*<<< orphan*/ ) ; 
 scalar_t__ Curl_checkheaders (struct connectdata const*,char const*) ; 
 scalar_t__ Curl_gmtime (int /*<<< orphan*/ ,struct tm*) ; 
 int /*<<< orphan*/ * Curl_month ; 
 int /*<<< orphan*/ * Curl_wkday ; 
 int /*<<< orphan*/  failf (struct Curl_easy*,char*) ; 
 int /*<<< orphan*/  msnprintf (char*,int,char*,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strlen (char*) ; 

CURLcode Curl_add_timecondition(const struct connectdata *conn,
                                Curl_send_buffer *req_buffer)
{
  struct Curl_easy *data = conn->data;
  const struct tm *tm;
  struct tm keeptime;
  CURLcode result;
  char datestr[80];
  const char *condp;

  if(data->set.timecondition == CURL_TIMECOND_NONE)
    /* no condition was asked for */
    return CURLE_OK;

  result = Curl_gmtime(data->set.timevalue, &keeptime);
  if(result) {
    failf(data, "Invalid TIMEVALUE");
    return result;
  }
  tm = &keeptime;

  switch(data->set.timecondition) {
  default:
    return CURLE_BAD_FUNCTION_ARGUMENT;

  case CURL_TIMECOND_IFMODSINCE:
    condp = "If-Modified-Since";
    break;
  case CURL_TIMECOND_IFUNMODSINCE:
    condp = "If-Unmodified-Since";
    break;
  case CURL_TIMECOND_LASTMOD:
    condp = "Last-Modified";
    break;
  }

  if(Curl_checkheaders(conn, condp)) {
    /* A custom header was specified; it will be sent instead. */
    return CURLE_OK;
  }

  /* The If-Modified-Since header family should have their times set in
   * GMT as RFC2616 defines: "All HTTP date/time stamps MUST be
   * represented in Greenwich Mean Time (GMT), without exception. For the
   * purposes of HTTP, GMT is exactly equal to UTC (Coordinated Universal
   * Time)." (see page 20 of RFC2616).
   */

  /* format: "Tue, 15 Nov 1994 12:45:26 GMT" */
  msnprintf(datestr, sizeof(datestr),
            "%s: %s, %02d %s %4d %02d:%02d:%02d GMT\r\n",
            condp,
            Curl_wkday[tm->tm_wday?tm->tm_wday-1:6],
            tm->tm_mday,
            Curl_month[tm->tm_mon],
            tm->tm_year + 1900,
            tm->tm_hour,
            tm->tm_min,
            tm->tm_sec);

  result = Curl_add_buffer(&req_buffer, datestr, strlen(datestr));

  return result;
}