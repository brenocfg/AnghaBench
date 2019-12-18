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
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_2__ {scalar_t__ u8; } ;
struct sha256_ctx {int inlen; TYPE_1__ in; int /*<<< orphan*/  len; } ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (scalar_t__,int /*<<< orphan*/  const*,unsigned int) ; 
 int /*<<< orphan*/  sha256_block (struct sha256_ctx*) ; 

__attribute__((used)) static void sha256_chunk(struct sha256_ctx *p,
      const uint8_t *s, unsigned len)
{
   p->len += len;

   while (len)
   {
      unsigned l = 64 - p->inlen;

      if (len < l)
         l       = len;

      memcpy(p->in.u8 + p->inlen, s, l);

      s         += l;
      p->inlen  += l;
      len       -= l;

      if (p->inlen == 64)
         sha256_block(p);
   }
}