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

/* Variables and functions */

__attribute__((used)) static size_t trhash_compare(void *k1, size_t k1_len, void *k2, size_t k2_len)
{
  (void)k1_len;
  (void)k2_len;

  return *(struct Curl_easy **)k1 == *(struct Curl_easy **)k2;
}