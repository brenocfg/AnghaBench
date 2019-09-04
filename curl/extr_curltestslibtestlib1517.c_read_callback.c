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
struct WriteThis {size_t sizeleft; size_t readptr; } ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (void*,size_t,size_t) ; 
 int /*<<< orphan*/  wait_ms (int) ; 

__attribute__((used)) static size_t read_callback(void *ptr, size_t size, size_t nmemb, void *userp)
{
  struct WriteThis *pooh = (struct WriteThis *)userp;
  size_t tocopy = size * nmemb;

  /* Wait one second before return POST data          *
   * so libcurl will wait before sending request body */
  wait_ms(1000);

  if(tocopy < 1 || !pooh->sizeleft)
    return 0;

  if(pooh->sizeleft < tocopy)
    tocopy = pooh->sizeleft;

  memcpy(ptr, pooh->readptr, tocopy);/* copy requested data */
  pooh->readptr += tocopy;           /* advance pointer */
  pooh->sizeleft -= tocopy;          /* less data left */
  return tocopy;
}