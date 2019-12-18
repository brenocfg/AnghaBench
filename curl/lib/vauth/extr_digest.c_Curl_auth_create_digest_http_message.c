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
struct digestdata {int algo; } ;
struct Curl_easy {int dummy; } ;
typedef  int /*<<< orphan*/  CURLcode ;

/* Variables and functions */
#define  CURLDIGESTALGO_MD5 133 
#define  CURLDIGESTALGO_MD5SESS 132 
#define  CURLDIGESTALGO_SHA256 131 
#define  CURLDIGESTALGO_SHA256SESS 130 
#define  CURLDIGESTALGO_SHA512_256 129 
#define  CURLDIGESTALGO_SHA512_256SESS 128 
 int /*<<< orphan*/  CURLE_UNSUPPORTED_PROTOCOL ; 
 int /*<<< orphan*/  Curl_md5it ; 
 int /*<<< orphan*/  Curl_sha256it ; 
 int /*<<< orphan*/  _Curl_auth_create_digest_http_message (struct Curl_easy*,char const*,char const*,unsigned char const*,unsigned char const*,struct digestdata*,char**,size_t*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  auth_digest_md5_to_ascii ; 
 int /*<<< orphan*/  auth_digest_sha256_to_ascii ; 

CURLcode Curl_auth_create_digest_http_message(struct Curl_easy *data,
                                              const char *userp,
                                              const char *passwdp,
                                              const unsigned char *request,
                                              const unsigned char *uripath,
                                              struct digestdata *digest,
                                              char **outptr, size_t *outlen)
{
  switch(digest->algo) {
  case CURLDIGESTALGO_MD5:
  case CURLDIGESTALGO_MD5SESS:
    return _Curl_auth_create_digest_http_message(data, userp, passwdp,
                                                 request, uripath, digest,
                                                 outptr, outlen,
                                                 auth_digest_md5_to_ascii,
                                                 Curl_md5it);

  case CURLDIGESTALGO_SHA256:
  case CURLDIGESTALGO_SHA256SESS:
  case CURLDIGESTALGO_SHA512_256:
  case CURLDIGESTALGO_SHA512_256SESS:
    return _Curl_auth_create_digest_http_message(data, userp, passwdp,
                                                 request, uripath, digest,
                                                 outptr, outlen,
                                                 auth_digest_sha256_to_ascii,
                                                 Curl_sha256it);

  default:
    return CURLE_UNSUPPORTED_PROTOCOL;
  }
}