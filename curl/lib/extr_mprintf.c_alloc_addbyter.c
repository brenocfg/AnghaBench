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
struct asprintf {char* buffer; int fail; int alloc; int len; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 char* malloc (int) ; 
 char* realloc (char*,size_t) ; 

__attribute__((used)) static int alloc_addbyter(int output, FILE *data)
{
  struct asprintf *infop = (struct asprintf *)data;
  unsigned char outc = (unsigned char)output;

  if(!infop->buffer) {
    infop->buffer = malloc(32);
    if(!infop->buffer) {
      infop->fail = 1;
      return -1; /* fail */
    }
    infop->alloc = 32;
    infop->len = 0;
  }
  else if(infop->len + 1 >= infop->alloc) {
    char *newptr = NULL;
    size_t newsize = infop->alloc*2;

    /* detect wrap-around or other overflow problems */
    if(newsize > infop->alloc)
      newptr = realloc(infop->buffer, newsize);

    if(!newptr) {
      infop->fail = 1;
      return -1; /* fail */
    }
    infop->buffer = newptr;
    infop->alloc = newsize;
  }

  infop->buffer[ infop->len ] = outc;

  infop->len++;

  return outc; /* fputc() returns like this on success */
}