#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {size_t maxlen; char* src_string; char* buffer_base; size_t real_len; int pseudo_len; char* dest_string; scalar_t__ buffer_len; } ;
typedef  TYPE_1__ xprintf_struct ;

/* Variables and functions */
 int EOF ; 
 int dispatch (TYPE_1__*) ; 
 int /*<<< orphan*/  free (char*) ; 
 scalar_t__ realloc (void*,size_t) ; 
 int realloc_buff (TYPE_1__*,size_t) ; 

__attribute__((used)) static int core(xprintf_struct *s)
{
  size_t save_len;
  char *dummy_base;

  /* basic checks */
  if ((int)(s->maxlen) <= 0) /* 'int' to check against some conversion */
    return EOF;           /* error for example if value is (int)-10 */
  s->maxlen--;      /* because initial maxlen counts final 0 */
  /* note: now 'maxlen' _can_ be zero */

  if (s->src_string == NULL)
    s->src_string = "(null)";

  /* struct init and memory allocation */
  s->buffer_base = NULL;
  s->buffer_len = 0;
  s->real_len = 0;
  s->pseudo_len = 0;
  if (realloc_buff(s, (size_t)0) == EOF)
    return EOF;
  s->dest_string = s->buffer_base;

  /* process source string */
  for (;;) {
    /* up to end of source string */
    if (*(s->src_string) == 0) {
      *(s->dest_string) = '\0';    /* final NUL */
      break;
    }

    if (dispatch(s) == EOF)
      goto free_EOF;

    /* up to end of dest string */
    if (s->real_len >= s->maxlen) {
      (s->buffer_base)[s->maxlen] = '\0'; /* final NUL */
      break;
    }
  }

  /* for (v)asnprintf */
  dummy_base = s->buffer_base;

  dummy_base = s->buffer_base + s->real_len;
  save_len = s->real_len;

  /* process the remaining of source string to compute 'pseudo_len'. We
   * overwrite again and again, starting at 'dummy_base' because we don't
   * need the text, only char count. */
  while(*(s->src_string) != 0) { /* up to end of source string */
    s->real_len = 0;
    s->dest_string = dummy_base;
    if (dispatch(s) == EOF)
      goto free_EOF;
  }

  s->buffer_base = (char *)realloc((void *)(s->buffer_base), save_len + 1);
  if (s->buffer_base == NULL)
    return EOF; /* should rarely happen because we shrink the buffer */
  return s->pseudo_len;

 free_EOF:
  free(s->buffer_base);
  return EOF;
}