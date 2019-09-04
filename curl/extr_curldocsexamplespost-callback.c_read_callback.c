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

__attribute__((used)) static size_t read_callback(void *dest, size_t size, size_t nmemb, void *userp)
{
  struct WriteThis *wt = (struct WriteThis *)userp;
  size_t buffer_size = size*nmemb;

  if(wt->sizeleft) {
    /* copy as much as possible from the source to the destination */
    size_t copy_this_much = wt->sizeleft;
    if(copy_this_much > buffer_size)
      copy_this_much = buffer_size;
    memcpy(dest, wt->readptr, copy_this_much);

    wt->readptr += copy_this_much;
    wt->sizeleft -= copy_this_much;
    return copy_this_much; /* we copied this many bytes */
  }

  return 0; /* no more data left to deliver */
}