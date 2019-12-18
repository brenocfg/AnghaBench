#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {scalar_t__ avail_out; void* next_out; scalar_t__ avail_in; void* next_in; } ;
struct zlib {scalar_t__ state; int window_bits; scalar_t__ rc; TYPE_1__ z; scalar_t__ uncompressed_digits; scalar_t__ compressed_digits; } ;

/* Variables and functions */
 void* Z_NULL ; 
 scalar_t__ Z_OK ; 
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ inflateReset2 (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zlib_message (struct zlib*,int) ; 

__attribute__((used)) static int
zlib_reset(struct zlib *zlib, int window_bits)
   /* Reinitializes a zlib with a different window_bits */
{
   assert(zlib->state >= 0); /* initialized by zlib_init */

   zlib->z.next_in = Z_NULL;
   zlib->z.avail_in = 0;
   zlib->z.next_out = Z_NULL;
   zlib->z.avail_out = 0;

   zlib->window_bits = window_bits;
   zlib->compressed_digits = 0;
   zlib->uncompressed_digits = 0;

   zlib->state = 0; /* initialized, once */
   zlib->rc = inflateReset2(&zlib->z, 0);
   if (zlib->rc != Z_OK)
   {
      zlib_message(zlib, 1/*unexpected*/);
      return 0;
   }

   return 1;
}