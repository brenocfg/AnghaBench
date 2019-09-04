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
typedef  int /*<<< orphan*/  FILE ;
typedef  int /*<<< orphan*/  CURL ;

/* Variables and functions */
 int /*<<< orphan*/  CURLOPT_WRITEDATA ; 
 int CURL_PUSH_DENY ; 
 int CURL_PUSH_OK ; 
 int /*<<< orphan*/  curl_easy_setopt (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 char* curl_pushheader_byname (struct curl_pushheaders*,char*) ; 
 char* curl_pushheader_bynum (struct curl_pushheaders*,size_t) ; 
 int /*<<< orphan*/ * fopen (char*,char*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static int server_push_callback(CURL *parent,
                                CURL *easy,
                                size_t num_headers,
                                struct curl_pushheaders *headers,
                                void *userp)
{
  char *headp;
  size_t i;
  int *transfers = (int *)userp;
  char filename[128];
  FILE *out;
  static unsigned int count = 0;

  (void)parent; /* we have no use for this */

  snprintf(filename, 128, "push%u", count++);

  /* here's a new stream, save it in a new file for each new push */
  out = fopen(filename, "wb");
  if(!out) {
    /* if we can't save it, deny it */
    fprintf(stderr, "Failed to create output file for push\n");
    return CURL_PUSH_DENY;
  }

  /* write to this file */
  curl_easy_setopt(easy, CURLOPT_WRITEDATA, out);

  fprintf(stderr, "**** push callback approves stream %u, got %lu headers!\n",
          count, (unsigned long)num_headers);

  for(i = 0; i<num_headers; i++) {
    headp = curl_pushheader_bynum(headers, i);
    fprintf(stderr, "**** header %lu: %s\n", (unsigned long)i, headp);
  }

  headp = curl_pushheader_byname(headers, ":path");
  if(headp) {
    fprintf(stderr, "**** The PATH is %s\n", headp /* skip :path + colon */);
  }

  (*transfers)++; /* one more */
  return CURL_PUSH_OK;
}