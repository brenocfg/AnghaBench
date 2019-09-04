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
 scalar_t__ Curl_base64_decode (char*,unsigned char**,size_t*) ; 
 int GPE_OK ; 
 int GPE_OUT_OF_MEMORY ; 
 int /*<<< orphan*/  free (unsigned char*) ; 
 int /*<<< orphan*/  memcpy (char*,unsigned char*,size_t) ; 

__attribute__((used)) static int decodedata(char  **buf,   /* dest buffer */
                      size_t *len)   /* dest buffer data length */
{
  CURLcode error = CURLE_OK;
  unsigned char *buf64 = NULL;
  size_t src_len = 0;

  if(!*len)
    return GPE_OK;

  /* base64 decode the given buffer */
  error = Curl_base64_decode(*buf, &buf64, &src_len);
  if(error)
    return GPE_OUT_OF_MEMORY;

  if(!src_len) {
    /*
    ** currently there is no way to tell apart an OOM condition in
    ** Curl_base64_decode() from zero length decoded data. For now,
    ** let's just assume it is an OOM condition, currently we have
    ** no input for this function that decodes to zero length data.
    */
    free(buf64);

    return GPE_OUT_OF_MEMORY;
  }

  /* memcpy to support binary blobs */
  memcpy(*buf, buf64, src_len);
  *len = src_len;
  *(*buf + src_len) = '\0';

  free(buf64);

  return GPE_OK;
}