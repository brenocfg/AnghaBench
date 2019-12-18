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
typedef  TYPE_1__* z_streamp ;
struct internal_state_deflate {int wrap; } ;
struct TYPE_3__ {unsigned int avail_in; unsigned int next_in; unsigned int total_in; int /*<<< orphan*/  adler; scalar_t__ state; } ;
typedef  int /*<<< orphan*/  Bytef ;

/* Variables and functions */
 int /*<<< orphan*/  adler32 (int /*<<< orphan*/ ,int /*<<< orphan*/ *,unsigned int) ; 
 int /*<<< orphan*/  crc32 (int /*<<< orphan*/ ,int /*<<< orphan*/ *,unsigned int) ; 
 int /*<<< orphan*/  zmemcpy (int /*<<< orphan*/ *,unsigned int,unsigned int) ; 

__attribute__((used)) static int read_buf(z_streamp strm, Bytef *buf, unsigned size)
{
   struct internal_state_deflate *state = (struct internal_state_deflate*)strm->state;
   unsigned len = strm->avail_in;

   if (len > size) len = size;
   if (len == 0) return 0;

   strm->avail_in  -= len;

   zmemcpy(buf, strm->next_in, len);
   if (state->wrap == 1) {
      strm->adler = adler32(strm->adler, buf, len);
   }
#ifdef GZIP
   else if (state->wrap == 2) {
      strm->adler = crc32(strm->adler, buf, len);
   }
#endif
   strm->next_in  += len;
   strm->total_in += len;

   return (int)len;
}