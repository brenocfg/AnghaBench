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
typedef  int uint8_t ;

/* Variables and functions */

__attribute__((used)) static size_t BrotliParseAsUTF8(
    int* symbol, const uint8_t* input, size_t size) {
  /* ASCII */
  if ((input[0] & 0x80) == 0) {
    *symbol = input[0];
    if (*symbol > 0) {
      return 1;
    }
  }
  /* 2-byte UTF8 */
  if (size > 1u &&
      (input[0] & 0xE0) == 0xC0 &&
      (input[1] & 0xC0) == 0x80) {
    *symbol = (((input[0] & 0x1F) << 6) |
               (input[1] & 0x3F));
    if (*symbol > 0x7F) {
      return 2;
    }
  }
  /* 3-byte UFT8 */
  if (size > 2u &&
      (input[0] & 0xF0) == 0xE0 &&
      (input[1] & 0xC0) == 0x80 &&
      (input[2] & 0xC0) == 0x80) {
    *symbol = (((input[0] & 0x0F) << 12) |
               ((input[1] & 0x3F) << 6) |
               (input[2] & 0x3F));
    if (*symbol > 0x7FF) {
      return 3;
    }
  }
  /* 4-byte UFT8 */
  if (size > 3u &&
      (input[0] & 0xF8) == 0xF0 &&
      (input[1] & 0xC0) == 0x80 &&
      (input[2] & 0xC0) == 0x80 &&
      (input[3] & 0xC0) == 0x80) {
    *symbol = (((input[0] & 0x07) << 18) |
               ((input[1] & 0x3F) << 12) |
               ((input[2] & 0x3F) << 6) |
               (input[3] & 0x3F));
    if (*symbol > 0xFFFF && *symbol <= 0x10FFFF) {
      return 4;
    }
  }
  /* Not UTF8, emit a special symbol above the UTF8-code space */
  *symbol = 0x110000 | input[0];
  return 1;
}