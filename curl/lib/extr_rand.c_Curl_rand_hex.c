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
typedef  int /*<<< orphan*/  buffer ;
typedef  scalar_t__ CURLcode ;

/* Variables and functions */
 scalar_t__ CURLE_BAD_FUNCTION_ARGUMENT ; 
 scalar_t__ Curl_rand (struct Curl_easy*,unsigned char*,size_t) ; 
 int /*<<< orphan*/  DEBUGASSERT (int) ; 
 int /*<<< orphan*/  memset (unsigned char*,int /*<<< orphan*/ ,int) ; 

CURLcode Curl_rand_hex(struct Curl_easy *data, unsigned char *rnd,
                       size_t num)
{
  CURLcode result = CURLE_BAD_FUNCTION_ARGUMENT;
  const char *hex = "0123456789abcdef";
  unsigned char buffer[128];
  unsigned char *bufp = buffer;
  DEBUGASSERT(num > 1);

#ifdef __clang_analyzer__
  /* This silences a scan-build warning about accessing this buffer with
     uninitialized memory. */
  memset(buffer, 0, sizeof(buffer));
#endif

  if((num/2 >= sizeof(buffer)) || !(num&1))
    /* make sure it fits in the local buffer and that it is an odd number! */
    return CURLE_BAD_FUNCTION_ARGUMENT;

  num--; /* save one for zero termination */

  result = Curl_rand(data, buffer, num/2);
  if(result)
    return result;

  while(num) {
    /* clang-tidy warns on this line without this comment: */
    /* NOLINTNEXTLINE(clang-analyzer-core.UndefinedBinaryOperatorResult) */
    *rnd++ = hex[(*bufp & 0xF0)>>4];
    *rnd++ = hex[*bufp & 0x0F];
    bufp++;
    num -= 2;
  }
  *rnd = 0;

  return result;
}