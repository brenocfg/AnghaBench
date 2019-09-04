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
struct Curl_handler {int flags; } ;
struct Curl_URL {char* user; char* password; char* options; } ;
typedef  scalar_t__ CURLcode ;
typedef  int /*<<< orphan*/  CURLUcode ;

/* Variables and functions */
 int /*<<< orphan*/  CURLUE_MALFORMED_INPUT ; 
 int /*<<< orphan*/  CURLUE_OK ; 
 int /*<<< orphan*/  CURLUE_USER_NOT_ALLOWED ; 
 unsigned int CURLU_DISALLOW_USER ; 
 scalar_t__ Curl_parse_login_details (char*,int,char**,char**,char**) ; 
 int PROTOPT_URLOPTIONS ; 
 int /*<<< orphan*/  free (char*) ; 
 char* strchr (char*,char) ; 

__attribute__((used)) static CURLUcode parse_hostname_login(struct Curl_URL *u,
                                      const struct Curl_handler *h,
                                      char **hostname,
                                      unsigned int flags)
{
  CURLUcode result = CURLUE_OK;
  CURLcode ccode;
  char *userp = NULL;
  char *passwdp = NULL;
  char *optionsp = NULL;

  /* At this point, we're hoping all the other special cases have
   * been taken care of, so conn->host.name is at most
   *    [user[:password][;options]]@]hostname
   *
   * We need somewhere to put the embedded details, so do that first.
   */

  char *ptr = strchr(*hostname, '@');
  char *login = *hostname;

  if(!ptr)
    goto out;

  /* We will now try to extract the
   * possible login information in a string like:
   * ftp://user:password@ftp.my.site:8021/README */
  *hostname = ++ptr;

  /* We could use the login information in the URL so extract it. Only parse
     options if the handler says we should. Note that 'h' might be NULL! */
  ccode = Curl_parse_login_details(login, ptr - login - 1,
                                   &userp, &passwdp,
                                   (h && (h->flags & PROTOPT_URLOPTIONS)) ?
                                   &optionsp:NULL);
  if(ccode) {
    result = CURLUE_MALFORMED_INPUT;
    goto out;
  }

  if(userp) {
    if(flags & CURLU_DISALLOW_USER) {
      /* Option DISALLOW_USER is set and url contains username. */
      result = CURLUE_USER_NOT_ALLOWED;
      goto out;
    }

    u->user = userp;
  }

  if(passwdp)
    u->password = passwdp;

  if(optionsp)
    u->options = optionsp;

  return CURLUE_OK;
  out:

  free(userp);
  free(passwdp);
  free(optionsp);

  return result;
}