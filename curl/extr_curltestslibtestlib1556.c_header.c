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
struct headerinfo {size_t largest; } ;

/* Variables and functions */

__attribute__((used)) static size_t header(void *ptr, size_t size, size_t nmemb, void *stream)
{
  size_t headersize = size * nmemb;
  struct headerinfo *info = (struct headerinfo *)stream;
  (void)ptr;

  if(headersize > info->largest)
    /* remember the longest header */
    info->largest = headersize;

  return nmemb * size;
}