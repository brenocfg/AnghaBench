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
struct zlib_trans_stream {int /*<<< orphan*/  ex; } ;

/* Variables and functions */
 int /*<<< orphan*/  MAX_WBITS ; 
 scalar_t__ calloc (int,int) ; 

__attribute__((used)) static void *zlib_inflate_stream_new(void)
{
   struct zlib_trans_stream *ret = (struct zlib_trans_stream*)calloc(1, sizeof(struct zlib_trans_stream));
   if (!ret)
      return NULL;
   ret->ex = MAX_WBITS;
   return (void *) ret;
}