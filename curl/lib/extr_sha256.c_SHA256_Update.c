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
struct sha256_state {int curlen; unsigned long length; unsigned char* buf; } ;

/* Variables and functions */
 unsigned long CURLMIN (unsigned long,unsigned long) ; 
 unsigned long block_size ; 
 int /*<<< orphan*/  memcpy (unsigned char*,unsigned char const*,unsigned long) ; 
 scalar_t__ sha256_compress (struct sha256_state*,unsigned char*) ; 

__attribute__((used)) static int SHA256_Update(struct sha256_state *md,
                         const unsigned char *in,
                         unsigned long inlen)
{
  unsigned long n;
#define block_size 64
  if(md->curlen > sizeof(md->buf))
    return -1;
  while(inlen > 0) {
    if(md->curlen == 0 && inlen >= block_size) {
      if(sha256_compress(md, (unsigned char *)in) < 0)
        return -1;
      md->length += block_size * 8;
      in += block_size;
      inlen -= block_size;
    }
    else {
      n = CURLMIN(inlen, (block_size - md->curlen));
      memcpy(md->buf + md->curlen, in, n);
      md->curlen += n;
      in += n;
      inlen -= n;
      if(md->curlen == block_size) {
        if(sha256_compress(md, md->buf) < 0)
          return -1;
        md->length += 8 * block_size;
        md->curlen = 0;
      }
    }
  }
  return 0;
}