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
struct TYPE_3__ {int /*<<< orphan*/  subparts; } ;
typedef  TYPE_1__ tool_mime ;
typedef  int /*<<< orphan*/  curl_mime ;
typedef  scalar_t__ CURLcode ;
typedef  int /*<<< orphan*/  CURL ;

/* Variables and functions */
 scalar_t__ CURLE_OK ; 
 scalar_t__ CURLE_OUT_OF_MEMORY ; 
 int /*<<< orphan*/  curl_mime_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * curl_mime_init (int /*<<< orphan*/ *) ; 
 scalar_t__ tool2curlparts (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

CURLcode tool2curlmime(CURL *curl, tool_mime *m, curl_mime **mime)
{
  CURLcode ret = CURLE_OK;

  *mime = curl_mime_init(curl);
  if(!*mime)
    ret = CURLE_OUT_OF_MEMORY;
  else
    ret = tool2curlparts(curl, m->subparts, *mime);
  if(ret) {
    curl_mime_free(*mime);
    *mime = NULL;
  }
  return ret;
}