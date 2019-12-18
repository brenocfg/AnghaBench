#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  timebuf ;
typedef  scalar_t__ time_t ;
struct tm {size_t tm_mon; int /*<<< orphan*/  tm_sec; int /*<<< orphan*/  tm_min; int /*<<< orphan*/  tm_hour; int /*<<< orphan*/  tm_year; int /*<<< orphan*/  tm_mday; int /*<<< orphan*/  tm_wday; } ;
struct ftp_conn {int /*<<< orphan*/  file; } ;
struct TYPE_7__ {struct ftp_conn ftpc; } ;
struct connectdata {TYPE_2__ proto; struct Curl_easy* data; } ;
struct FTP {void* transfer; } ;
struct TYPE_10__ {scalar_t__ filetime; void* timecond; } ;
struct TYPE_9__ {int timecondition; scalar_t__ timevalue; int /*<<< orphan*/  get_filetime; int /*<<< orphan*/  opt_no_body; } ;
struct TYPE_8__ {int /*<<< orphan*/ * buffer; } ;
struct TYPE_6__ {struct FTP* protop; } ;
struct Curl_easy {TYPE_5__ info; TYPE_4__ set; TYPE_3__ state; TYPE_1__ req; } ;
typedef  int /*<<< orphan*/  headerbuf ;
typedef  scalar_t__ CURLcode ;

/* Variables and functions */
 int /*<<< orphan*/  CLIENTWRITE_BOTH ; 
 scalar_t__ CURLE_FTP_COULDNT_RETR_FILE ; 
 scalar_t__ CURLE_OK ; 
#define  CURL_TIMECOND_IFMODSINCE 129 
#define  CURL_TIMECOND_IFUNMODSINCE 128 
 scalar_t__ Curl_client_write (struct connectdata*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 scalar_t__ Curl_gmtime (scalar_t__,struct tm*) ; 
 int /*<<< orphan*/ * Curl_month ; 
 int /*<<< orphan*/ * Curl_wkday ; 
 void* FTPTRANSFER_NONE ; 
 int /*<<< orphan*/  FTP_STOP ; 
 void* TRUE ; 
 scalar_t__ curl_getdate (char*,scalar_t__*) ; 
 int /*<<< orphan*/  failf (struct Curl_easy*,char*) ; 
 scalar_t__ ftp_state_type (struct connectdata*) ; 
 int /*<<< orphan*/  infof (struct Curl_easy*,char*) ; 
 int /*<<< orphan*/  msnprintf (char*,int,char*,int,int,int,int,int,int,...) ; 
 int sscanf (int /*<<< orphan*/ *,char*,int*,int*,int*,int*,int*,int*) ; 
 int /*<<< orphan*/  state (struct connectdata*,int /*<<< orphan*/ ) ; 
 scalar_t__ time (int /*<<< orphan*/ *) ; 

__attribute__((used)) static CURLcode ftp_state_mdtm_resp(struct connectdata *conn,
                                    int ftpcode)
{
  CURLcode result = CURLE_OK;
  struct Curl_easy *data = conn->data;
  struct FTP *ftp = data->req.protop;
  struct ftp_conn *ftpc = &conn->proto.ftpc;

  switch(ftpcode) {
  case 213:
    {
      /* we got a time. Format should be: "YYYYMMDDHHMMSS[.sss]" where the
         last .sss part is optional and means fractions of a second */
      int year, month, day, hour, minute, second;
      if(6 == sscanf(&data->state.buffer[4], "%04d%02d%02d%02d%02d%02d",
                     &year, &month, &day, &hour, &minute, &second)) {
        /* we have a time, reformat it */
        char timebuf[24];
        time_t secs = time(NULL);

        msnprintf(timebuf, sizeof(timebuf),
                  "%04d%02d%02d %02d:%02d:%02d GMT",
                  year, month, day, hour, minute, second);
        /* now, convert this into a time() value: */
        data->info.filetime = curl_getdate(timebuf, &secs);
      }

#ifdef CURL_FTP_HTTPSTYLE_HEAD
      /* If we asked for a time of the file and we actually got one as well,
         we "emulate" a HTTP-style header in our output. */

      if(data->set.opt_no_body &&
         ftpc->file &&
         data->set.get_filetime &&
         (data->info.filetime >= 0) ) {
        char headerbuf[128];
        time_t filetime = data->info.filetime;
        struct tm buffer;
        const struct tm *tm = &buffer;

        result = Curl_gmtime(filetime, &buffer);
        if(result)
          return result;

        /* format: "Tue, 15 Nov 1994 12:45:26" */
        msnprintf(headerbuf, sizeof(headerbuf),
                  "Last-Modified: %s, %02d %s %4d %02d:%02d:%02d GMT\r\n",
                  Curl_wkday[tm->tm_wday?tm->tm_wday-1:6],
                  tm->tm_mday,
                  Curl_month[tm->tm_mon],
                  tm->tm_year + 1900,
                  tm->tm_hour,
                  tm->tm_min,
                  tm->tm_sec);
        result = Curl_client_write(conn, CLIENTWRITE_BOTH, headerbuf, 0);
        if(result)
          return result;
      } /* end of a ridiculous amount of conditionals */
#endif
    }
    break;
  default:
    infof(data, "unsupported MDTM reply format\n");
    break;
  case 550: /* "No such file or directory" */
    failf(data, "Given file does not exist");
    result = CURLE_FTP_COULDNT_RETR_FILE;
    break;
  }

  if(data->set.timecondition) {
    if((data->info.filetime > 0) && (data->set.timevalue > 0)) {
      switch(data->set.timecondition) {
      case CURL_TIMECOND_IFMODSINCE:
      default:
        if(data->info.filetime <= data->set.timevalue) {
          infof(data, "The requested document is not new enough\n");
          ftp->transfer = FTPTRANSFER_NONE; /* mark to not transfer data */
          data->info.timecond = TRUE;
          state(conn, FTP_STOP);
          return CURLE_OK;
        }
        break;
      case CURL_TIMECOND_IFUNMODSINCE:
        if(data->info.filetime > data->set.timevalue) {
          infof(data, "The requested document is not old enough\n");
          ftp->transfer = FTPTRANSFER_NONE; /* mark to not transfer data */
          data->info.timecond = TRUE;
          state(conn, FTP_STOP);
          return CURLE_OK;
        }
        break;
      } /* switch */
    }
    else {
      infof(data, "Skipping time comparison\n");
    }
  }

  if(!result)
    result = ftp_state_type(conn);

  return result;
}