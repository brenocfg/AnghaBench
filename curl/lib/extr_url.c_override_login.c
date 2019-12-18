#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {void* user_passwd; void* netrc; } ;
struct TYPE_6__ {int /*<<< orphan*/  name; } ;
struct connectdata {TYPE_3__ bits; TYPE_2__ host; } ;
struct TYPE_8__ {int /*<<< orphan*/  uh; } ;
struct TYPE_5__ {scalar_t__ use_netrc; scalar_t__* str; } ;
struct Curl_easy {TYPE_4__ state; TYPE_1__ set; } ;
typedef  int /*<<< orphan*/  CURLcode ;
typedef  scalar_t__ CURLUcode ;

/* Variables and functions */
 int /*<<< orphan*/  CURLE_OK ; 
 int /*<<< orphan*/  CURLE_OUT_OF_MEMORY ; 
 int /*<<< orphan*/  CURLUPART_PASSWORD ; 
 int /*<<< orphan*/  CURLUPART_USER ; 
 scalar_t__ CURL_NETRC_IGNORED ; 
 scalar_t__ CURL_NETRC_REQUIRED ; 
 int Curl_parsenetrc (int /*<<< orphan*/ ,char**,char**,int*,int*,scalar_t__) ; 
 int /*<<< orphan*/  Curl_safefree (char*) ; 
 int /*<<< orphan*/  Curl_uc_to_curlcode (scalar_t__) ; 
 void* FALSE ; 
 size_t STRING_NETRC_FILE ; 
 size_t STRING_OPTIONS ; 
 size_t STRING_PASSWORD ; 
 size_t STRING_USERNAME ; 
 void* TRUE ; 
 scalar_t__ curl_url_set (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  infof (struct Curl_easy*,char*,int /*<<< orphan*/ ) ; 
 char* strdup (scalar_t__) ; 

__attribute__((used)) static CURLcode override_login(struct Curl_easy *data,
                               struct connectdata *conn,
                               char **userp, char **passwdp, char **optionsp)
{
  bool user_changed = FALSE;
  bool passwd_changed = FALSE;
  CURLUcode uc;

  if(data->set.use_netrc == CURL_NETRC_REQUIRED && conn->bits.user_passwd) {
    /* ignore user+password in the URL */
    if(*userp) {
      Curl_safefree(*userp);
      user_changed = TRUE;
    }
    if(*passwdp) {
      Curl_safefree(*passwdp);
      passwd_changed = TRUE;
    }
    conn->bits.user_passwd = FALSE; /* disable user+password */
  }

  if(data->set.str[STRING_USERNAME]) {
    free(*userp);
    *userp = strdup(data->set.str[STRING_USERNAME]);
    if(!*userp)
      return CURLE_OUT_OF_MEMORY;
    conn->bits.user_passwd = TRUE; /* enable user+password */
    user_changed = TRUE;
  }

  if(data->set.str[STRING_PASSWORD]) {
    free(*passwdp);
    *passwdp = strdup(data->set.str[STRING_PASSWORD]);
    if(!*passwdp)
      return CURLE_OUT_OF_MEMORY;
    conn->bits.user_passwd = TRUE; /* enable user+password */
    passwd_changed = TRUE;
  }

  if(data->set.str[STRING_OPTIONS]) {
    free(*optionsp);
    *optionsp = strdup(data->set.str[STRING_OPTIONS]);
    if(!*optionsp)
      return CURLE_OUT_OF_MEMORY;
  }

  conn->bits.netrc = FALSE;
  if(data->set.use_netrc != CURL_NETRC_IGNORED &&
      (!*userp || !**userp || !*passwdp || !**passwdp)) {
    bool netrc_user_changed = FALSE;
    bool netrc_passwd_changed = FALSE;
    int ret;

    ret = Curl_parsenetrc(conn->host.name,
                          userp, passwdp,
                          &netrc_user_changed, &netrc_passwd_changed,
                          data->set.str[STRING_NETRC_FILE]);
    if(ret > 0) {
      infof(data, "Couldn't find host %s in the .netrc file; using defaults\n",
            conn->host.name);
    }
    else if(ret < 0) {
      return CURLE_OUT_OF_MEMORY;
    }
    else {
      /* set bits.netrc TRUE to remember that we got the name from a .netrc
         file, so that it is safe to use even if we followed a Location: to a
         different host or similar. */
      conn->bits.netrc = TRUE;
      conn->bits.user_passwd = TRUE; /* enable user+password */

      if(netrc_user_changed) {
        user_changed = TRUE;
      }
      if(netrc_passwd_changed) {
        passwd_changed = TRUE;
      }
    }
  }

  /* for updated strings, we update them in the URL */
  if(user_changed) {
    uc = curl_url_set(data->state.uh, CURLUPART_USER, *userp, 0);
    if(uc)
      return Curl_uc_to_curlcode(uc);
  }
  if(passwd_changed) {
    uc = curl_url_set(data->state.uh, CURLUPART_PASSWORD, *passwdp, 0);
    if(uc)
      return Curl_uc_to_curlcode(uc);
  }
  return CURLE_OK;
}