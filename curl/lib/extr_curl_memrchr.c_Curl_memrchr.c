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

/* Variables and functions */

void *
Curl_memrchr(const void *s, int c, size_t n)
{
  if(n > 0) {
    const unsigned char *p = s;
    const unsigned char *q = s;

    p += n - 1;

    while(p >= q) {
      if(*p == (unsigned char)c)
        return (void *)p;
      p--;
    }
  }
  return NULL;
}