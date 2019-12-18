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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  BROTLI_BOOL ;

/* Variables and functions */
 size_t BrotliParseAsUTF8 (int*,int /*<<< orphan*/  const*,size_t const) ; 
 int /*<<< orphan*/  TO_BROTLI_BOOL (int) ; 

BROTLI_BOOL BrotliIsMostlyUTF8(
    const uint8_t* data, const size_t pos, const size_t mask,
    const size_t length, const double min_fraction) {
  size_t size_utf8 = 0;
  size_t i = 0;
  while (i < length) {
    int symbol;
    size_t bytes_read =
        BrotliParseAsUTF8(&symbol, &data[(pos + i) & mask], length - i);
    i += bytes_read;
    if (symbol < 0x110000) size_utf8 += bytes_read;
  }
  return TO_BROTLI_BOOL(size_utf8 > min_fraction * (double)length);
}