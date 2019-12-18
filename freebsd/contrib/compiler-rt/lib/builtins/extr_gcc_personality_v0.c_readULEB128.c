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

/* Variables and functions */

__attribute__((used)) static uintptr_t readULEB128(const uint8_t **data) {
  uintptr_t result = 0;
  uintptr_t shift = 0;
  unsigned char byte;
  const uint8_t *p = *data;
  do {
    byte = *p++;
    result |= (byte & 0x7f) << shift;
    shift += 7;
  } while (byte & 0x80);
  *data = p;
  return result;
}