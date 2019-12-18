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
struct userdata {char* text; int counter; } ;
typedef  int curl_lock_data ;
typedef  int /*<<< orphan*/  CURL ;

/* Variables and functions */
#define  CURL_LOCK_DATA_COOKIE 131 
#define  CURL_LOCK_DATA_DNS 130 
#define  CURL_LOCK_DATA_SHARE 129 
#define  CURL_LOCK_DATA_SSL_SESSION 128 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  printf (char*,char const*,char*,int) ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static void my_unlock(CURL *handle, curl_lock_data data, void *useptr)
{
  const char *what;
  struct userdata *user = (struct userdata *)useptr;
  (void)handle;
  switch(data) {
    case CURL_LOCK_DATA_SHARE:
      what = "share";
      break;
    case CURL_LOCK_DATA_DNS:
      what = "dns";
      break;
    case CURL_LOCK_DATA_COOKIE:
      what = "cookie";
      break;
    case CURL_LOCK_DATA_SSL_SESSION:
      what = "ssl_session";
      break;
    default:
      fprintf(stderr, "unlock: no such data: %d\n", (int)data);
      return;
  }
  printf("unlock: %-6s [%s]: %d\n", what, user->text, user->counter);
  user->counter++;
}