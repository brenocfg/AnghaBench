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
typedef  int /*<<< orphan*/  FILE ;
typedef  scalar_t__ CURLcode ;
typedef  int /*<<< orphan*/  CURL ;

/* Variables and functions */
 scalar_t__ CURLE_OK ; 
 int /*<<< orphan*/  CURLOPT_CAINFO ; 
 int /*<<< orphan*/  CURLOPT_HEADERDATA ; 
 int /*<<< orphan*/  CURLOPT_KEYPASSWD ; 
 int /*<<< orphan*/  CURLOPT_SSLCERT ; 
 int /*<<< orphan*/  CURLOPT_SSLCERTTYPE ; 
 int /*<<< orphan*/  CURLOPT_SSLENGINE ; 
 int /*<<< orphan*/  CURLOPT_SSLENGINE_DEFAULT ; 
 int /*<<< orphan*/  CURLOPT_SSLKEY ; 
 int /*<<< orphan*/  CURLOPT_SSLKEYTYPE ; 
 int /*<<< orphan*/  CURLOPT_SSL_VERIFYPEER ; 
 int /*<<< orphan*/  CURLOPT_URL ; 
 int /*<<< orphan*/  CURL_GLOBAL_DEFAULT ; 
 int /*<<< orphan*/  curl_easy_cleanup (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * curl_easy_init () ; 
 scalar_t__ curl_easy_perform (int /*<<< orphan*/ *) ; 
 scalar_t__ curl_easy_setopt (int /*<<< orphan*/ *,int /*<<< orphan*/ ,...) ; 
 char* curl_easy_strerror (scalar_t__) ; 
 int /*<<< orphan*/  curl_global_cleanup () ; 
 int /*<<< orphan*/  curl_global_init (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * fopen (char const*,char*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  stderr ; 

int main(void)
{
  CURL *curl;
  CURLcode res;
  FILE *headerfile;
  const char *pPassphrase = NULL;

  static const char *pCertFile = "testcert.pem";
  static const char *pCACertFile = "cacert.pem";
  static const char *pHeaderFile = "dumpit";

  const char *pKeyName;
  const char *pKeyType;

  const char *pEngine;

#ifdef USE_ENGINE
  pKeyName  = "rsa_test";
  pKeyType  = "ENG";
  pEngine   = "chil";            /* for nChiper HSM... */
#else
  pKeyName  = "testkey.pem";
  pKeyType  = "PEM";
  pEngine   = NULL;
#endif

  headerfile = fopen(pHeaderFile, "wb");

  curl_global_init(CURL_GLOBAL_DEFAULT);

  curl = curl_easy_init();
  if(curl) {
    /* what call to write: */
    curl_easy_setopt(curl, CURLOPT_URL, "HTTPS://your.favourite.ssl.site");
    curl_easy_setopt(curl, CURLOPT_HEADERDATA, headerfile);

    do { /* dummy loop, just to break out from */
      if(pEngine) {
        /* use crypto engine */
        if(curl_easy_setopt(curl, CURLOPT_SSLENGINE, pEngine) != CURLE_OK) {
          /* load the crypto engine */
          fprintf(stderr, "can't set crypto engine\n");
          break;
        }
        if(curl_easy_setopt(curl, CURLOPT_SSLENGINE_DEFAULT, 1L) != CURLE_OK) {
          /* set the crypto engine as default */
          /* only needed for the first time you load
             a engine in a curl object... */
          fprintf(stderr, "can't set crypto engine as default\n");
          break;
        }
      }
      /* cert is stored PEM coded in file... */
      /* since PEM is default, we needn't set it for PEM */
      curl_easy_setopt(curl, CURLOPT_SSLCERTTYPE, "PEM");

      /* set the cert for client authentication */
      curl_easy_setopt(curl, CURLOPT_SSLCERT, pCertFile);

      /* sorry, for engine we must set the passphrase
         (if the key has one...) */
      if(pPassphrase)
        curl_easy_setopt(curl, CURLOPT_KEYPASSWD, pPassphrase);

      /* if we use a key stored in a crypto engine,
         we must set the key type to "ENG" */
      curl_easy_setopt(curl, CURLOPT_SSLKEYTYPE, pKeyType);

      /* set the private key (file or ID in engine) */
      curl_easy_setopt(curl, CURLOPT_SSLKEY, pKeyName);

      /* set the file with the certs vaildating the server */
      curl_easy_setopt(curl, CURLOPT_CAINFO, pCACertFile);

      /* disconnect if we can't validate server's cert */
      curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 1L);

      /* Perform the request, res will get the return code */
      res = curl_easy_perform(curl);
      /* Check for errors */
      if(res != CURLE_OK)
        fprintf(stderr, "curl_easy_perform() failed: %s\n",
                curl_easy_strerror(res));

      /* we are done... */
    } while(0);
    /* always cleanup */
    curl_easy_cleanup(curl);
  }

  curl_global_cleanup();

  return 0;
}