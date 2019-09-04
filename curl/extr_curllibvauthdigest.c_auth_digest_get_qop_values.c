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
typedef  int /*<<< orphan*/  CURLcode ;

/* Variables and functions */
 int /*<<< orphan*/  CURLE_OK ; 
 int /*<<< orphan*/  CURLE_OUT_OF_MEMORY ; 
 int DIGEST_QOP_VALUE_AUTH ; 
 int DIGEST_QOP_VALUE_AUTH_CONF ; 
 int DIGEST_QOP_VALUE_AUTH_INT ; 
 int /*<<< orphan*/  DIGEST_QOP_VALUE_STRING_AUTH ; 
 int /*<<< orphan*/  DIGEST_QOP_VALUE_STRING_AUTH_CONF ; 
 int /*<<< orphan*/  DIGEST_QOP_VALUE_STRING_AUTH_INT ; 
 int /*<<< orphan*/  free (char*) ; 
 scalar_t__ strcasecompare (char*,int /*<<< orphan*/ ) ; 
 char* strdup (char const*) ; 
 char* strtok_r (char*,char*,char**) ; 

__attribute__((used)) static CURLcode auth_digest_get_qop_values(const char *options, int *value)
{
  char *tmp;
  char *token;
  char *tok_buf = NULL;

  /* Initialise the output */
  *value = 0;

  /* Tokenise the list of qop values. Use a temporary clone of the buffer since
     strtok_r() ruins it. */
  tmp = strdup(options);
  if(!tmp)
    return CURLE_OUT_OF_MEMORY;

  token = strtok_r(tmp, ",", &tok_buf);
  while(token != NULL) {
    if(strcasecompare(token, DIGEST_QOP_VALUE_STRING_AUTH))
      *value |= DIGEST_QOP_VALUE_AUTH;
    else if(strcasecompare(token, DIGEST_QOP_VALUE_STRING_AUTH_INT))
      *value |= DIGEST_QOP_VALUE_AUTH_INT;
    else if(strcasecompare(token, DIGEST_QOP_VALUE_STRING_AUTH_CONF))
      *value |= DIGEST_QOP_VALUE_AUTH_CONF;

    token = strtok_r(NULL, ",", &tok_buf);
  }

  free(tmp);

  return CURLE_OK;
}