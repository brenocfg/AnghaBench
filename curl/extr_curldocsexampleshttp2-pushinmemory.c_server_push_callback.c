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
struct curl_pushheaders {int dummy; } ;
typedef  int /*<<< orphan*/  CURL ;

/* Variables and functions */
 int /*<<< orphan*/  CURLOPT_WRITEDATA ; 
 int CURL_PUSH_DENY ; 
 int CURL_PUSH_OK ; 
 size_t MAX_FILES ; 
 int /*<<< orphan*/  curl_easy_setopt (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 char* curl_pushheader_byname (struct curl_pushheaders*,char*) ; 
 int /*<<< orphan*/ * files ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  init_memory (int /*<<< orphan*/ *) ; 
 size_t pushindex ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static int server_push_callback(CURL *parent,
                                CURL *easy,
                                size_t num_headers,
                                struct curl_pushheaders *headers,
                                void *userp)
{
  char *headp;
  int *transfers = (int *)userp;
  (void)parent; /* we have no use for this */
  (void)num_headers; /* unused */

  if(pushindex == MAX_FILES)
    /* can't fit anymore */
    return CURL_PUSH_DENY;

  /* write to this buffer */
  init_memory(&files[pushindex]);
  curl_easy_setopt(easy, CURLOPT_WRITEDATA, &files[pushindex]);
  pushindex++;

  headp = curl_pushheader_byname(headers, ":path");
  if(headp)
    fprintf(stderr, "* Pushed :path '%s'\n", headp /* skip :path + colon */);

  (*transfers)++; /* one more */
  return CURL_PUSH_OK;
}