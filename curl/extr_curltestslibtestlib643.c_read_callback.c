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
struct WriteThis {char* readptr; scalar_t__ sizeleft; } ;

/* Variables and functions */

__attribute__((used)) static size_t read_callback(char *ptr, size_t size, size_t nmemb, void *userp)
{
#ifdef LIB644
  (void)ptr;
  (void)size;
  (void)nmemb;
  (void)userp;
  return CURL_READFUNC_ABORT;
#else

  struct WriteThis *pooh = (struct WriteThis *)userp;
  int eof = !*pooh->readptr;

  if(size*nmemb < 1)
    return 0;

#ifndef LIB645
  eof = pooh->sizeleft <= 0;
  if(!eof)
    pooh->sizeleft--;
#endif

  if(!eof) {
    *ptr = *pooh->readptr;           /* copy one single byte */
    pooh->readptr++;                 /* advance pointer */
    return 1;                        /* we return 1 byte at a time! */
  }

  return 0;                         /* no more data left to deliver */
#endif
}