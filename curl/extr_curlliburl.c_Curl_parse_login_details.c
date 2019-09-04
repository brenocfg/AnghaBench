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
typedef  scalar_t__ CURLcode ;

/* Variables and functions */
 scalar_t__ CURLE_OK ; 
 scalar_t__ CURLE_OUT_OF_MEMORY ; 
 int /*<<< orphan*/  Curl_safefree (char*) ; 
 int /*<<< orphan*/  free (char*) ; 
 char* malloc (size_t) ; 
 int /*<<< orphan*/  memcpy (char*,char const*,size_t) ; 
 char* strchr (char const*,char) ; 

CURLcode Curl_parse_login_details(const char *login, const size_t len,
                                  char **userp, char **passwdp,
                                  char **optionsp)
{
  CURLcode result = CURLE_OK;
  char *ubuf = NULL;
  char *pbuf = NULL;
  char *obuf = NULL;
  const char *psep = NULL;
  const char *osep = NULL;
  size_t ulen;
  size_t plen;
  size_t olen;

  /* Attempt to find the password separator */
  if(passwdp) {
    psep = strchr(login, ':');

    /* Within the constraint of the login string */
    if(psep >= login + len)
      psep = NULL;
  }

  /* Attempt to find the options separator */
  if(optionsp) {
    osep = strchr(login, ';');

    /* Within the constraint of the login string */
    if(osep >= login + len)
      osep = NULL;
  }

  /* Calculate the portion lengths */
  ulen = (psep ?
          (size_t)(osep && psep > osep ? osep - login : psep - login) :
          (osep ? (size_t)(osep - login) : len));
  plen = (psep ?
          (osep && osep > psep ? (size_t)(osep - psep) :
                                 (size_t)(login + len - psep)) - 1 : 0);
  olen = (osep ?
          (psep && psep > osep ? (size_t)(psep - osep) :
                                 (size_t)(login + len - osep)) - 1 : 0);

  /* Allocate the user portion buffer */
  if(userp && ulen) {
    ubuf = malloc(ulen + 1);
    if(!ubuf)
      result = CURLE_OUT_OF_MEMORY;
  }

  /* Allocate the password portion buffer */
  if(!result && passwdp && plen) {
    pbuf = malloc(plen + 1);
    if(!pbuf) {
      free(ubuf);
      result = CURLE_OUT_OF_MEMORY;
    }
  }

  /* Allocate the options portion buffer */
  if(!result && optionsp && olen) {
    obuf = malloc(olen + 1);
    if(!obuf) {
      free(pbuf);
      free(ubuf);
      result = CURLE_OUT_OF_MEMORY;
    }
  }

  if(!result) {
    /* Store the user portion if necessary */
    if(ubuf) {
      memcpy(ubuf, login, ulen);
      ubuf[ulen] = '\0';
      Curl_safefree(*userp);
      *userp = ubuf;
    }

    /* Store the password portion if necessary */
    if(pbuf) {
      memcpy(pbuf, psep + 1, plen);
      pbuf[plen] = '\0';
      Curl_safefree(*passwdp);
      *passwdp = pbuf;
    }

    /* Store the options portion if necessary */
    if(obuf) {
      memcpy(obuf, osep + 1, olen);
      obuf[olen] = '\0';
      Curl_safefree(*optionsp);
      *optionsp = obuf;
    }
  }

  return result;
}