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
struct hostname {char* dispname; char* name; char* encalloc; } ;
struct connectdata {struct Curl_easy* data; } ;
struct Curl_easy {int dummy; } ;
typedef  int /*<<< orphan*/  CURLcode ;

/* Variables and functions */
 int /*<<< orphan*/  CURLE_OK ; 
 int /*<<< orphan*/  CURLE_URL_MALFORMAT ; 
 int IDN2_NFC_INPUT ; 
 int IDN2_NONTRANSITIONAL ; 
 int IDN2_OK ; 
 int /*<<< orphan*/  IDN2_VERSION ; 
 scalar_t__ curl_win32_idn_to_ascii (char*,char**) ; 
 int /*<<< orphan*/  failf (struct Curl_easy*,char*,char*,...) ; 
 scalar_t__ idn2_check_version (int /*<<< orphan*/ ) ; 
 int idn2_lookup_ul (char const*,char**,int) ; 
 int /*<<< orphan*/  idn2_strerror (int) ; 
 int /*<<< orphan*/  infof (struct Curl_easy*,char*) ; 
 int /*<<< orphan*/  is_ASCII_name (char*) ; 

__attribute__((used)) static CURLcode idnconvert_hostname(struct connectdata *conn,
                                    struct hostname *host)
{
  struct Curl_easy *data = conn->data;

#ifndef USE_LIBIDN2
  (void)data;
  (void)conn;
#elif defined(CURL_DISABLE_VERBOSE_STRINGS)
  (void)conn;
#endif

  /* set the name we use to display the host name */
  host->dispname = host->name;

  /* Check name for non-ASCII and convert hostname to ACE form if we can */
  if(!is_ASCII_name(host->name)) {
#ifdef USE_LIBIDN2
    if(idn2_check_version(IDN2_VERSION)) {
      char *ace_hostname = NULL;
#if IDN2_VERSION_NUMBER >= 0x00140000
      /* IDN2_NFC_INPUT: Normalize input string using normalization form C.
         IDN2_NONTRANSITIONAL: Perform Unicode TR46 non-transitional
         processing. */
      int flags = IDN2_NFC_INPUT | IDN2_NONTRANSITIONAL;
#else
      int flags = IDN2_NFC_INPUT;
#endif
      int rc = idn2_lookup_ul((const char *)host->name, &ace_hostname, flags);
      if(rc == IDN2_OK) {
        host->encalloc = (char *)ace_hostname;
        /* change the name pointer to point to the encoded hostname */
        host->name = host->encalloc;
      }
      else {
        failf(data, "Failed to convert %s to ACE; %s\n", host->name,
              idn2_strerror(rc));
        return CURLE_URL_MALFORMAT;
      }
    }
#elif defined(USE_WIN32_IDN)
    char *ace_hostname = NULL;

    if(curl_win32_idn_to_ascii(host->name, &ace_hostname)) {
      host->encalloc = ace_hostname;
      /* change the name pointer to point to the encoded hostname */
      host->name = host->encalloc;
    }
    else {
      failf(data, "Failed to convert %s to ACE;\n", host->name);
      return CURLE_URL_MALFORMAT;
    }
#else
    infof(data, "IDN support not present, can't parse Unicode domains\n");
#endif
  }
  return CURLE_OK;
}