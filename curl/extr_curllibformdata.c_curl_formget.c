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
struct curl_httppost {int dummy; } ;
typedef  int /*<<< orphan*/  curl_mimepart ;
typedef  size_t (* curl_formget_callback ) (void*,char*,size_t) ;
typedef  int /*<<< orphan*/  buffer ;
typedef  scalar_t__ CURLcode ;

/* Variables and functions */
 scalar_t__ CURLE_READ_ERROR ; 
#define  CURL_READFUNC_ABORT 129 
#define  CURL_READFUNC_PAUSE 128 
 scalar_t__ Curl_getformdata (int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct curl_httppost*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Curl_mime_cleanpart (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Curl_mime_initpart (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ Curl_mime_prepare_headers (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 size_t Curl_mime_read (char*,int,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  MIMESTRATEGY_FORM ; 

int curl_formget(struct curl_httppost *form, void *arg,
                 curl_formget_callback append)
{
  CURLcode result;
  curl_mimepart toppart;

  Curl_mime_initpart(&toppart, NULL); /* default form is empty */
  result = Curl_getformdata(NULL, &toppart, form, NULL);
  if(!result)
    result = Curl_mime_prepare_headers(&toppart, "multipart/form-data",
                                       NULL, MIMESTRATEGY_FORM);

  while(!result) {
    char buffer[8192];
    size_t nread = Curl_mime_read(buffer, 1, sizeof(buffer), &toppart);

    if(!nread)
      break;

    switch(nread) {
    default:
      if(append(arg, buffer, nread) != nread)
        result = CURLE_READ_ERROR;
      break;
    case CURL_READFUNC_ABORT:
    case CURL_READFUNC_PAUSE:
      break;
    }
  }

  Curl_mime_cleanpart(&toppart);
  return (int) result;
}