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
struct sha256_state {int curlen; int length; unsigned char* buf; int /*<<< orphan*/ * state; } ;

/* Variables and functions */
 int /*<<< orphan*/  WPA_PUT_BE32 (unsigned char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WPA_PUT_BE64 (unsigned char*,int) ; 
 int /*<<< orphan*/  sha256_compress (struct sha256_state*,unsigned char*) ; 

__attribute__((used)) static int SHA256_Final(unsigned char *out,
                        struct sha256_state *md)
{
  int i;
  if(md->curlen >= sizeof(md->buf))
    return -1;
  /* increase the length of the message */
  md->length += md->curlen * 8;
  /* append the '1' bit */
  md->buf[md->curlen++] = (unsigned char)0x80;
  /* if the length is currently above 56 bytes we append zeros
   * then compress.  Then we can fall back to padding zeros and length
   * encoding like normal.
   */
  if(md->curlen > 56) {
    while(md->curlen < 64) {
      md->buf[md->curlen++] = (unsigned char)0;
    }
    sha256_compress(md, md->buf);
    md->curlen = 0;
  }
  /* pad up to 56 bytes of zeroes */
  while(md->curlen < 56) {
    md->buf[md->curlen++] = (unsigned char)0;
  }
  /* store length */
  WPA_PUT_BE64(md->buf + 56, md->length);
  sha256_compress(md, md->buf);
  /* copy output */
  for(i = 0; i < 8; i++)
    WPA_PUT_BE32(out + (4 * i), md->state[i]);
  return 0;
}