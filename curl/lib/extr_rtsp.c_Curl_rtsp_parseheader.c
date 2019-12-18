#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct connectdata {struct Curl_easy* data; } ;
struct RTSP {long CSeq_recv; } ;
struct TYPE_6__ {char** str; } ;
struct TYPE_5__ {long rtsp_CSeq_recv; } ;
struct TYPE_4__ {struct RTSP* protop; } ;
struct Curl_easy {TYPE_3__ set; TYPE_2__ state; TYPE_1__ req; } ;
typedef  int /*<<< orphan*/  CURLcode ;

/* Variables and functions */
 int /*<<< orphan*/  CURLE_OK ; 
 int /*<<< orphan*/  CURLE_OUT_OF_MEMORY ; 
 int /*<<< orphan*/  CURLE_RTSP_CSEQ_ERROR ; 
 int /*<<< orphan*/  CURLE_RTSP_SESSION_ERROR ; 
 scalar_t__ ISSPACE (char) ; 
 size_t STRING_RTSP_SESSION_ID ; 
 scalar_t__ checkprefix (char*,char*) ; 
 int /*<<< orphan*/  failf (struct Curl_easy*,char*,...) ; 
 char* malloc (int) ; 
 int /*<<< orphan*/  memcpy (char*,char*,int) ; 
 int sscanf (char*,char*,long*) ; 
 int /*<<< orphan*/  strlen (char*) ; 
 scalar_t__ strncmp (char*,char*,int /*<<< orphan*/ ) ; 

CURLcode Curl_rtsp_parseheader(struct connectdata *conn,
                               char *header)
{
  struct Curl_easy *data = conn->data;
  long CSeq = 0;

  if(checkprefix("CSeq:", header)) {
    /* Store the received CSeq. Match is verified in rtsp_done */
    int nc = sscanf(&header[4], ": %ld", &CSeq);
    if(nc == 1) {
      struct RTSP *rtsp = data->req.protop;
      rtsp->CSeq_recv = CSeq; /* mark the request */
      data->state.rtsp_CSeq_recv = CSeq; /* update the handle */
    }
    else {
      failf(data, "Unable to read the CSeq header: [%s]", header);
      return CURLE_RTSP_CSEQ_ERROR;
    }
  }
  else if(checkprefix("Session:", header)) {
    char *start;

    /* Find the first non-space letter */
    start = header + 8;
    while(*start && ISSPACE(*start))
      start++;

    if(!*start) {
      failf(data, "Got a blank Session ID");
    }
    else if(data->set.str[STRING_RTSP_SESSION_ID]) {
      /* If the Session ID is set, then compare */
      if(strncmp(start, data->set.str[STRING_RTSP_SESSION_ID],
                 strlen(data->set.str[STRING_RTSP_SESSION_ID]))  != 0) {
        failf(data, "Got RTSP Session ID Line [%s], but wanted ID [%s]",
              start, data->set.str[STRING_RTSP_SESSION_ID]);
        return CURLE_RTSP_SESSION_ERROR;
      }
    }
    else {
      /* If the Session ID is not set, and we find it in a response, then set
       * it.
       *
       * Allow any non whitespace content, up to the field separator or end of
       * line. RFC 2326 isn't 100% clear on the session ID and for example
       * gstreamer does url-encoded session ID's not covered by the standard.
       */
      char *end = start;
      while(*end && *end != ';' && !ISSPACE(*end))
        end++;

      /* Copy the id substring into a new buffer */
      data->set.str[STRING_RTSP_SESSION_ID] = malloc(end - start + 1);
      if(data->set.str[STRING_RTSP_SESSION_ID] == NULL)
        return CURLE_OUT_OF_MEMORY;
      memcpy(data->set.str[STRING_RTSP_SESSION_ID], start, end - start);
      (data->set.str[STRING_RTSP_SESSION_ID])[end - start] = '\0';
    }
  }
  return CURLE_OK;
}