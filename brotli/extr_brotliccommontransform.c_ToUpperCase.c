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

__attribute__((used)) static int ToUpperCase(uint8_t* p) {
  if (p[0] < 0xC0) {
    if (p[0] >= 'a' && p[0] <= 'z') {
      p[0] ^= 32;
    }
    return 1;
  }
  /* An overly simplified uppercasing model for UTF-8. */
  if (p[0] < 0xE0) {
    p[1] ^= 32;
    return 2;
  }
  /* An arbitrary transform for three byte characters. */
  p[2] ^= 5;
  return 3;
}