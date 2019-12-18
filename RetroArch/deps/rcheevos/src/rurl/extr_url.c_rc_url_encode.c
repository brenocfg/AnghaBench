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

/* Variables and functions */
 int /*<<< orphan*/  snprintf (char*,size_t,char*,unsigned char) ; 

__attribute__((used)) static int rc_url_encode(char* encoded, size_t len, const char* str) {
  for (;;) {
    switch (*str) {
      case 'a': case 'b': case 'c': case 'd': case 'e': case 'f': case 'g': case 'h': case 'i': case 'j':
      case 'k': case 'l': case 'm': case 'n': case 'o': case 'p': case 'q': case 'r': case 's': case 't':
      case 'u': case 'v': case 'w': case 'x': case 'y': case 'z':
      case 'A': case 'B': case 'C': case 'D': case 'E': case 'F': case 'G': case 'H': case 'I': case 'J':
      case 'K': case 'L': case 'M': case 'N': case 'O': case 'P': case 'Q': case 'R': case 'S': case 'T':
      case 'U': case 'V': case 'W': case 'X': case 'Y': case 'Z':
      case '0': case '1': case '2': case '3': case '4': case '5': case '6': case '7': case '8': case '9':
      case '-': case '_': case '.': case '~':
        if (len >= 2) {
          *encoded++ = *str++;
          len--;
        }
        else {
          return -1;
        }

        break;
      
      default:
        if (len >= 4) {
          snprintf(encoded, len, "%%%02x", (unsigned char)*str);
          encoded += 3;
          str++;
          len -= 3;
        }
        else {
          return -1;
        }

        break;
      
      case 0:
        *encoded = 0;
        return 0;
    }
  }
}