#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_2__* z_streamp ;
typedef  char* voidp ;
typedef  TYPE_3__* gz_statep ;
typedef  int /*<<< orphan*/ * gzFile ;
struct TYPE_9__ {int have; unsigned int next; unsigned int pos; } ;
struct TYPE_10__ {scalar_t__ avail_in; unsigned int avail_out; unsigned char* next_out; } ;
struct TYPE_11__ {scalar_t__ mode; scalar_t__ err; int past; scalar_t__ how; int size; TYPE_1__ x; scalar_t__ eof; int /*<<< orphan*/  skip; scalar_t__ seek; TYPE_2__ strm; } ;

/* Variables and functions */
 scalar_t__ GZ_READ ; 
 scalar_t__ LOOK ; 
 scalar_t__ MODE_COPY ; 
 scalar_t__ Z_BUF_ERROR ; 
 int /*<<< orphan*/  Z_DATA_ERROR ; 
 scalar_t__ Z_OK ; 
 int gz_decomp (TYPE_3__*) ; 
 int /*<<< orphan*/  gz_error (TYPE_3__*,int /*<<< orphan*/ ,char*) ; 
 int gz_fetch (TYPE_3__*) ; 
 int gz_load (TYPE_3__*,unsigned char*,unsigned int,unsigned int*) ; 
 int gz_skip (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (char*,unsigned int,unsigned int) ; 

int gzread(gzFile file, voidp buf, unsigned len)
{
   unsigned got, n;
   gz_statep state;
   z_streamp strm;

   /* get internal structure */
   if (file == NULL)
      return -1;
   state = (gz_statep)file;
   strm = &(state->strm);

   /* check that we're reading and that there's no (serious) error */
   if (state->mode != GZ_READ ||
         (state->err != Z_OK && state->err != Z_BUF_ERROR))
      return -1;

   /* since an int is returned, make sure len fits in one, otherwise return
      with an error (this avoids the flaw in the interface) */
   if ((int)len < 0) {
      gz_error(state, Z_DATA_ERROR, "requested length does not fit in int");
      return -1;
   }

   /* if len is zero, avoid unnecessary operations */
   if (len == 0)
      return 0;

   /* process a skip request */
   if (state->seek) {
      state->seek = 0;
      if (gz_skip(state, state->skip) == -1)
         return -1;
   }

   /* get len bytes to buf, or less than len if at the end */
   got = 0;
   n = 0;
   do {
      /* first just try copying data from the output buffer */
      if (state->x.have) {
         n = state->x.have > len ? len : state->x.have;
         memcpy(buf, state->x.next, n);
         state->x.next += n;
         state->x.have -= n;
      }

      /* output buffer empty -- return if we're at the end of the input */
      else if (state->eof && strm->avail_in == 0) {
         state->past = 1;        /* tried to read past end */
         break;
      }

      /* need output data -- for small len or new stream load up our output
         buffer */
      else if (state->how == LOOK || len < (state->size << 1)) {
         /* get more output, looking for header if required */
         if (gz_fetch(state) == -1)
            return -1;
         continue;       /* no progress yet -- go back to copy above */
         /* the copy above assures that we will leave with space in the
            output buffer, allowing at least one gzungetc() to succeed */
      }

      /* large len -- read directly into user buffer */
      else if (state->how == MODE_COPY) {      /* read directly */
         if (gz_load(state, (unsigned char *)buf, len, &n) == -1)
            return -1;
      }

      /* large len -- decompress directly into user buffer */
      else {  /* state->how == GZIP */
         strm->avail_out = len;
         strm->next_out = (unsigned char *)buf;
         if (gz_decomp(state) == -1)
            return -1;
         n = state->x.have;
         state->x.have = 0;
      }

      /* update progress */
      len -= n;
      buf = (char *)buf + n;
      got += n;
      state->x.pos += n;
   } while (len);

   /* return number of bytes read into user buffer (will fit in int) */
   return (int)got;
}