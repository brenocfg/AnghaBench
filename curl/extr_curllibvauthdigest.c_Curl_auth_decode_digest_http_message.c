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
struct digestdata {char* nonce; int nc; char* realm; char* opaque; char* qop; char* algorithm; void* stale; void* userhash; int /*<<< orphan*/  algo; } ;
typedef  int /*<<< orphan*/  CURLcode ;

/* Variables and functions */
 int /*<<< orphan*/  CURLDIGESTALGO_MD5 ; 
 int /*<<< orphan*/  CURLDIGESTALGO_MD5SESS ; 
 int /*<<< orphan*/  CURLDIGESTALGO_SHA256 ; 
 int /*<<< orphan*/  CURLDIGESTALGO_SHA256SESS ; 
 int /*<<< orphan*/  CURLDIGESTALGO_SHA512_256 ; 
 int /*<<< orphan*/  CURLDIGESTALGO_SHA512_256SESS ; 
 int /*<<< orphan*/  CURLE_BAD_CONTENT_ENCODING ; 
 int /*<<< orphan*/  CURLE_OK ; 
 int /*<<< orphan*/  CURLE_OUT_OF_MEMORY ; 
 int /*<<< orphan*/  Curl_auth_digest_cleanup (struct digestdata*) ; 
 scalar_t__ Curl_auth_digest_get_pair (char const*,char*,char*,char const**) ; 
 int DIGEST_MAX_CONTENT_LENGTH ; 
 int DIGEST_MAX_VALUE_LENGTH ; 
 char* DIGEST_QOP_VALUE_STRING_AUTH ; 
 char* DIGEST_QOP_VALUE_STRING_AUTH_INT ; 
 int FALSE ; 
 scalar_t__ ISSPACE (char const) ; 
 void* TRUE ; 
 int /*<<< orphan*/  free (char*) ; 
 scalar_t__ strcasecompare (char*,char*) ; 
 void* strdup (char*) ; 
 char* strtok_r (char*,char*,char**) ; 

CURLcode Curl_auth_decode_digest_http_message(const char *chlg,
                                              struct digestdata *digest)
{
  bool before = FALSE; /* got a nonce before */
  bool foundAuth = FALSE;
  bool foundAuthInt = FALSE;
  char *token = NULL;
  char *tmp = NULL;

  /* If we already have received a nonce, keep that in mind */
  if(digest->nonce)
    before = TRUE;

  /* Clean up any former leftovers and initialise to defaults */
  Curl_auth_digest_cleanup(digest);

  for(;;) {
    char value[DIGEST_MAX_VALUE_LENGTH];
    char content[DIGEST_MAX_CONTENT_LENGTH];

    /* Pass all additional spaces here */
    while(*chlg && ISSPACE(*chlg))
      chlg++;

    /* Extract a value=content pair */
    if(Curl_auth_digest_get_pair(chlg, value, content, &chlg)) {
      if(strcasecompare(value, "nonce")) {
        free(digest->nonce);
        digest->nonce = strdup(content);
        if(!digest->nonce)
          return CURLE_OUT_OF_MEMORY;
      }
      else if(strcasecompare(value, "stale")) {
        if(strcasecompare(content, "true")) {
          digest->stale = TRUE;
          digest->nc = 1; /* we make a new nonce now */
        }
      }
      else if(strcasecompare(value, "realm")) {
        free(digest->realm);
        digest->realm = strdup(content);
        if(!digest->realm)
          return CURLE_OUT_OF_MEMORY;
      }
      else if(strcasecompare(value, "opaque")) {
        free(digest->opaque);
        digest->opaque = strdup(content);
        if(!digest->opaque)
          return CURLE_OUT_OF_MEMORY;
      }
      else if(strcasecompare(value, "qop")) {
        char *tok_buf = NULL;
        /* Tokenize the list and choose auth if possible, use a temporary
           clone of the buffer since strtok_r() ruins it */
        tmp = strdup(content);
        if(!tmp)
          return CURLE_OUT_OF_MEMORY;

        token = strtok_r(tmp, ",", &tok_buf);
        while(token != NULL) {
          if(strcasecompare(token, DIGEST_QOP_VALUE_STRING_AUTH)) {
            foundAuth = TRUE;
          }
          else if(strcasecompare(token, DIGEST_QOP_VALUE_STRING_AUTH_INT)) {
            foundAuthInt = TRUE;
          }
          token = strtok_r(NULL, ",", &tok_buf);
        }

        free(tmp);

        /* Select only auth or auth-int. Otherwise, ignore */
        if(foundAuth) {
          free(digest->qop);
          digest->qop = strdup(DIGEST_QOP_VALUE_STRING_AUTH);
          if(!digest->qop)
            return CURLE_OUT_OF_MEMORY;
        }
        else if(foundAuthInt) {
          free(digest->qop);
          digest->qop = strdup(DIGEST_QOP_VALUE_STRING_AUTH_INT);
          if(!digest->qop)
            return CURLE_OUT_OF_MEMORY;
        }
      }
      else if(strcasecompare(value, "algorithm")) {
        free(digest->algorithm);
        digest->algorithm = strdup(content);
        if(!digest->algorithm)
          return CURLE_OUT_OF_MEMORY;

        if(strcasecompare(content, "MD5-sess"))
          digest->algo = CURLDIGESTALGO_MD5SESS;
        else if(strcasecompare(content, "MD5"))
          digest->algo = CURLDIGESTALGO_MD5;
        else if(strcasecompare(content, "SHA-256"))
          digest->algo = CURLDIGESTALGO_SHA256;
        else if(strcasecompare(content, "SHA-256-SESS"))
          digest->algo = CURLDIGESTALGO_SHA256SESS;
        else if(strcasecompare(content, "SHA-512-256"))
          digest->algo = CURLDIGESTALGO_SHA512_256;
        else if(strcasecompare(content, "SHA-512-256-SESS"))
          digest->algo = CURLDIGESTALGO_SHA512_256SESS;
        else
          return CURLE_BAD_CONTENT_ENCODING;
      }
      else if(strcasecompare(value, "userhash")) {
        if(strcasecompare(content, "true")) {
          digest->userhash = TRUE;
        }
      }
      else {
        /* Unknown specifier, ignore it! */
      }
    }
    else
      break; /* We're done here */

    /* Pass all additional spaces here */
    while(*chlg && ISSPACE(*chlg))
      chlg++;

    /* Allow the list to be comma-separated */
    if(',' == *chlg)
      chlg++;
  }

  /* We had a nonce since before, and we got another one now without
     'stale=true'. This means we provided bad credentials in the previous
     request */
  if(before && !digest->stale)
    return CURLE_BAD_CONTENT_ENCODING;

  /* We got this header without a nonce, that's a bad Digest line! */
  if(!digest->nonce)
    return CURLE_BAD_CONTENT_ENCODING;

  return CURLE_OK;
}