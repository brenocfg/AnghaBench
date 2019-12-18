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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int uint32_t ;
struct TYPE_3__ {int* i; int /*<<< orphan*/  buf; scalar_t__* in; } ;
typedef  TYPE_1__ MD5_CTX ;

/* Variables and functions */
 int /*<<< orphan*/  Transform (int /*<<< orphan*/ ,int*) ; 

void MD5Update(MD5_CTX *mdContext, uint8_t *inBuf, unsigned int inLen) {
  uint32_t     in[16];
  int          mdi;
  unsigned int i, ii;

  /* compute number of bytes mod 64 */
  mdi = (int)((mdContext->i[0] >> 3) & 0x3F);

  /* update number of bits */
  if ((mdContext->i[0] + ((uint32_t)inLen << 3)) < mdContext->i[0]) mdContext->i[1]++;
  mdContext->i[0] += ((uint32_t)inLen << 3);
  mdContext->i[1] += ((uint32_t)inLen >> 29);

  while (inLen--) {
    /* add new character to buffer, increment mdi */
    mdContext->in[mdi++] = *inBuf++;

    /* transform if necessary */
    if (mdi == 0x40) {
      for (i = 0, ii = 0; i < 16; i++, ii += 4)
        in[i] = (((uint32_t)mdContext->in[ii + 3]) << 24) | (((uint32_t)mdContext->in[ii + 2]) << 16) |
                (((uint32_t)mdContext->in[ii + 1]) << 8) | ((uint32_t)mdContext->in[ii]);
      Transform(mdContext->buf, in);
      mdi = 0;
    }
  }
}