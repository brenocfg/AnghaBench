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
 int /*<<< orphan*/  base64 ; 
 int /*<<< orphan*/  base64_encode (int /*<<< orphan*/ ,struct Curl_easy*,char const*,size_t,char**,size_t*) ; 

CURLcode Curl_base64_encode(struct Curl_easy *data,
                            const char *inputbuff, size_t insize,
                            char **outptr, size_t *outlen)
{
  return base64_encode(base64, data, inputbuff, insize, outptr, outlen);
}