#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {char* buf; long size; } ;
typedef  TYPE_1__ buffer_t ;

/* Variables and functions */
 long MIN_BYTE_GAIN ; 
 char* malloc (long) ; 
 char* realloc (char*,long) ; 

__attribute__((used)) static char *
get_buffer(buffer_t * buf, long size)

{
  char * cp;

  /* If `size' >= 0, make sure buffer at `buf' is at least `size'-byte long.
     Return the buffer address. */

  if(size < 0)
    return buf->buf;

  if(!buf->buf) {
    buf->buf = malloc(size);
    if(buf->buf)
      buf->size = size;

    return buf->buf;
  }

  if((unsigned long) size <= buf->size) {
    /* Shorten the buffer only if it frees a significant byte count. This
       avoids some realloc() overhead. */

    if(buf->size - size < MIN_BYTE_GAIN)
      return buf->buf;
  }

  /* Resize the buffer. */

  cp = realloc(buf->buf, size);
  if(cp) {
    buf->buf = cp;
    buf->size = size;
  }
  else if(size <= buf->size)
    cp = buf->buf;

  return cp;
}