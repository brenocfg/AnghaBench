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
struct SingleRequest {char* p; char* httpcode; } ;
struct Curl_easy {struct SingleRequest req; } ;

/* Variables and functions */
 int /*<<< orphan*/  failf (struct Curl_easy*,char*,char*) ; 
 char* strchr (char*,char) ; 
 int /*<<< orphan*/  strncmp (char*,char*,int) ; 

__attribute__((used)) static void print_http_error(struct Curl_easy *data)
{
  struct SingleRequest *k = &data->req;
  char *beg = k->p;

  /* make sure that data->req.p points to the HTTP status line */
  if(!strncmp(beg, "HTTP", 4)) {

    /* skip to HTTP status code */
    beg = strchr(beg, ' ');
    if(beg && *++beg) {

      /* find trailing CR */
      char end_char = '\r';
      char *end = strchr(beg, end_char);
      if(!end) {
        /* try to find LF (workaround for non-compliant HTTP servers) */
        end_char = '\n';
        end = strchr(beg, end_char);
      }

      if(end) {
        /* temporarily replace CR or LF by NUL and print the error message */
        *end = '\0';
        failf(data, "The requested URL returned error: %s", beg);

        /* restore the previously replaced CR or LF */
        *end = end_char;
        return;
      }
    }
  }

  /* fall-back to printing the HTTP status code only */
  failf(data, "The requested URL returned error: %d", k->httpcode);
}