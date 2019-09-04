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
struct Curl_easy {int dummy; } ;
typedef  int /*<<< orphan*/  HMAC_context ;
typedef  int /*<<< orphan*/  CURLcode ;

/* Variables and functions */
 int /*<<< orphan*/  CURLE_OK ; 
 int /*<<< orphan*/  CURLE_OUT_OF_MEMORY ; 
 int /*<<< orphan*/  Curl_HMAC_MD5 ; 
 int /*<<< orphan*/  Curl_HMAC_final (int /*<<< orphan*/ *,unsigned char*) ; 
 int /*<<< orphan*/ * Curl_HMAC_init (int /*<<< orphan*/ ,unsigned char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Curl_HMAC_update (int /*<<< orphan*/ *,unsigned char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Curl_base64_encode (struct Curl_easy*,char*,int /*<<< orphan*/ ,char**,size_t*) ; 
 int MD5_DIGEST_LEN ; 
 char* aprintf (char*,char const*,unsigned char,unsigned char,unsigned char,unsigned char,unsigned char,unsigned char,unsigned char,unsigned char,unsigned char,unsigned char,unsigned char,unsigned char,unsigned char,unsigned char,unsigned char,unsigned char) ; 
 int /*<<< orphan*/  curlx_uztoui (size_t) ; 
 int /*<<< orphan*/  free (char*) ; 
 size_t strlen (char const*) ; 

CURLcode Curl_auth_create_cram_md5_message(struct Curl_easy *data,
                                           const char *chlg,
                                           const char *userp,
                                           const char *passwdp,
                                           char **outptr, size_t *outlen)
{
  CURLcode result = CURLE_OK;
  size_t chlglen = 0;
  HMAC_context *ctxt;
  unsigned char digest[MD5_DIGEST_LEN];
  char *response;

  if(chlg)
    chlglen = strlen(chlg);

  /* Compute the digest using the password as the key */
  ctxt = Curl_HMAC_init(Curl_HMAC_MD5,
                        (const unsigned char *) passwdp,
                        curlx_uztoui(strlen(passwdp)));
  if(!ctxt)
    return CURLE_OUT_OF_MEMORY;

  /* Update the digest with the given challenge */
  if(chlglen > 0)
    Curl_HMAC_update(ctxt, (const unsigned char *) chlg,
                     curlx_uztoui(chlglen));

  /* Finalise the digest */
  Curl_HMAC_final(ctxt, digest);

  /* Generate the response */
  response = aprintf(
    "%s %02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x",
    userp, digest[0], digest[1], digest[2], digest[3], digest[4],
    digest[5], digest[6], digest[7], digest[8], digest[9], digest[10],
    digest[11], digest[12], digest[13], digest[14], digest[15]);
  if(!response)
    return CURLE_OUT_OF_MEMORY;

  /* Base64 encode the response */
  result = Curl_base64_encode(data, response, 0, outptr, outlen);

  free(response);

  return result;
}