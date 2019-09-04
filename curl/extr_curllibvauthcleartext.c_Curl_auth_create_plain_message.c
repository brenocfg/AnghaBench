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
typedef  int /*<<< orphan*/  CURLcode ;

/* Variables and functions */
 int /*<<< orphan*/  CURLE_OUT_OF_MEMORY ; 
 int /*<<< orphan*/  Curl_base64_encode (struct Curl_easy*,char*,size_t,char**,size_t*) ; 
 int SIZE_T_MAX ; 
 int /*<<< orphan*/  free (char*) ; 
 char* malloc (size_t) ; 
 int /*<<< orphan*/  memcpy (char*,char const*,size_t) ; 
 size_t strlen (char const*) ; 

CURLcode Curl_auth_create_plain_message(struct Curl_easy *data,
                                        const char *authzid,
                                        const char *authcid,
                                        const char *passwd,
                                        char **outptr, size_t *outlen)
{
  CURLcode result;
  char *plainauth;
  size_t zlen;
  size_t clen;
  size_t plen;
  size_t plainlen;

  *outlen = 0;
  *outptr = NULL;
  zlen = (authzid == NULL ? 0 : strlen(authzid));
  clen = strlen(authcid);
  plen = strlen(passwd);

  /* Compute binary message length. Check for overflows. */
  if(((zlen + clen) > SIZE_T_MAX/4) || (plen > (SIZE_T_MAX/2 - 2)))
    return CURLE_OUT_OF_MEMORY;
  plainlen = zlen + clen + plen + 2;

  plainauth = malloc(plainlen);
  if(!plainauth)
    return CURLE_OUT_OF_MEMORY;

  /* Calculate the reply */
  if(zlen != 0)
    memcpy(plainauth, authzid, zlen);
  plainauth[zlen] = '\0';
  memcpy(plainauth + zlen + 1, authcid, clen);
  plainauth[zlen + clen + 1] = '\0';
  memcpy(plainauth + zlen + clen + 2, passwd, plen);

  /* Base64 encode the reply */
  result = Curl_base64_encode(data, plainauth, plainlen, outptr, outlen);
  free(plainauth);

  return result;
}