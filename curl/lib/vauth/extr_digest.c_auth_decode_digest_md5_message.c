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
 scalar_t__ CURLE_BAD_CONTENT_ENCODING ; 
 scalar_t__ CURLE_OK ; 
 scalar_t__ Curl_base64_decode (char const*,unsigned char**,size_t*) ; 
 int /*<<< orphan*/  auth_digest_get_key_value (char*,char*,char*,size_t,char) ; 
 int /*<<< orphan*/  free (unsigned char*) ; 
 int /*<<< orphan*/  strcpy (char*,char*) ; 
 size_t strlen (char const*) ; 

__attribute__((used)) static CURLcode auth_decode_digest_md5_message(const char *chlg64,
                                               char *nonce, size_t nlen,
                                               char *realm, size_t rlen,
                                               char *alg, size_t alen,
                                               char *qop, size_t qlen)
{
  CURLcode result = CURLE_OK;
  unsigned char *chlg = NULL;
  size_t chlglen = 0;
  size_t chlg64len = strlen(chlg64);

  /* Decode the base-64 encoded challenge message */
  if(chlg64len && *chlg64 != '=') {
    result = Curl_base64_decode(chlg64, &chlg, &chlglen);
    if(result)
      return result;
  }

  /* Ensure we have a valid challenge message */
  if(!chlg)
    return CURLE_BAD_CONTENT_ENCODING;

  /* Retrieve nonce string from the challenge */
  if(!auth_digest_get_key_value((char *) chlg, "nonce=\"", nonce, nlen,
                                '\"')) {
    free(chlg);
    return CURLE_BAD_CONTENT_ENCODING;
  }

  /* Retrieve realm string from the challenge */
  if(!auth_digest_get_key_value((char *) chlg, "realm=\"", realm, rlen,
                                '\"')) {
    /* Challenge does not have a realm, set empty string [RFC2831] page 6 */
    strcpy(realm, "");
  }

  /* Retrieve algorithm string from the challenge */
  if(!auth_digest_get_key_value((char *) chlg, "algorithm=", alg, alen, ',')) {
    free(chlg);
    return CURLE_BAD_CONTENT_ENCODING;
  }

  /* Retrieve qop-options string from the challenge */
  if(!auth_digest_get_key_value((char *) chlg, "qop=\"", qop, qlen, '\"')) {
    free(chlg);
    return CURLE_BAD_CONTENT_ENCODING;
  }

  free(chlg);

  return CURLE_OK;
}