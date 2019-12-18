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
struct TYPE_3__ {size_t real_len; size_t buffer_len; char* buffer_base; char* dest_string; } ;
typedef  TYPE_1__ xprintf_struct ;

/* Variables and functions */
 size_t ALLOC_CHUNK ; 
 size_t ALLOC_SECURITY_MARGIN ; 
 int EOF ; 
 scalar_t__ realloc (void*,size_t) ; 

__attribute__((used)) static int realloc_buff(xprintf_struct *s, size_t len)
{
  char * ptr;

  if (len + ALLOC_SECURITY_MARGIN + s->real_len > s->buffer_len) {
    len += s->real_len + ALLOC_CHUNK;
    ptr = (char *)realloc((void *)(s->buffer_base), len);
    if (ptr == NULL) {
      s->buffer_base = NULL;
      return EOF;
    }

    s->dest_string = ptr + (size_t)(s->dest_string - s->buffer_base);
    s->buffer_base = ptr;
    s->buffer_len = len;

    (s->buffer_base)[s->buffer_len - 1] = 1; /* overflow marker */
  }

  return 0;
}