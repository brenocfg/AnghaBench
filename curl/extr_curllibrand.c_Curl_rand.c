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
 int /*<<< orphan*/  CURLE_BAD_FUNCTION_ARGUMENT ; 
 int /*<<< orphan*/  DEBUGASSERT (int) ; 
 int /*<<< orphan*/  randit (struct Curl_easy*,unsigned int*) ; 

CURLcode Curl_rand(struct Curl_easy *data, unsigned char *rnd, size_t num)
{
  CURLcode result = CURLE_BAD_FUNCTION_ARGUMENT;

  DEBUGASSERT(num > 0);

  while(num) {
    unsigned int r;
    size_t left = num < sizeof(unsigned int) ? num : sizeof(unsigned int);

    result = randit(data, &r);
    if(result)
      return result;

    while(left) {
      *rnd++ = (unsigned char)(r & 0xFF);
      r >>= 8;
      --num;
      --left;
    }
  }

  return result;
}