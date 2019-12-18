#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_2__* gz_statep ;
typedef  int /*<<< orphan*/ * gzFile ;
struct TYPE_5__ {unsigned int have; unsigned char* next; unsigned int pos; } ;
struct TYPE_6__ {scalar_t__ mode; scalar_t__ err; int past; TYPE_1__ x; int /*<<< orphan*/  skip; scalar_t__ seek; } ;

/* Variables and functions */
 scalar_t__ GZ_READ ; 
 scalar_t__ Z_BUF_ERROR ; 
 scalar_t__ Z_OK ; 
 int gz_fetch (TYPE_2__*) ; 
 int gz_skip (TYPE_2__*,int /*<<< orphan*/ ) ; 
 scalar_t__ memchr (unsigned char*,char,unsigned int) ; 
 int /*<<< orphan*/  memcpy (char*,unsigned char*,unsigned int) ; 

char * gzgets(gzFile file, char *buf, int len)
{
   unsigned left, n;
   char *str;
   unsigned char *eol;
   gz_statep state;

   /* check parameters and get internal structure */
   if (file == NULL || buf == NULL || len < 1)
      return NULL;
   state = (gz_statep)file;

   /* check that we're reading and that there's no (serious) error */
   if (state->mode != GZ_READ ||
         (state->err != Z_OK && state->err != Z_BUF_ERROR))
      return NULL;

   /* process a skip request */
   if (state->seek) {
      state->seek = 0;
      if (gz_skip(state, state->skip) == -1)
         return NULL;
   }

   /* copy output bytes up to new line or len - 1, whichever comes first --
      append a terminating zero to the string (we don't check for a zero in
      the contents, let the user worry about that) */
   str = buf;
   left = (unsigned)len - 1;
   if (left) do {
      /* assure that something is in the output buffer */
      if (state->x.have == 0 && gz_fetch(state) == -1)
         return NULL;                /* error */
      if (state->x.have == 0) {       /* end of file */
         state->past = 1;            /* read past end */
         break;                      /* return what we have */
      }

      /* look for end-of-line in current output buffer */
      n = state->x.have > left ? left : state->x.have;
      eol = (unsigned char *)memchr(state->x.next, '\n', n);
      if (eol != NULL)
         n = (unsigned)(eol - state->x.next) + 1;

      /* copy through end-of-line, or remainder if not found */
      memcpy(buf, state->x.next, n);
      state->x.have -= n;
      state->x.next += n;
      state->x.pos += n;
      left -= n;
      buf += n;
   } while (left && eol == NULL);

   /* return terminated string, or if nothing, end of file */
   if (buf == str)
      return NULL;
   buf[0] = 0;
   return str;
}