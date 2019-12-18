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
#define  RC_FORMAT_CENTISECS 133 
#define  RC_FORMAT_FRAMES 132 
#define  RC_FORMAT_OTHER 131 
#define  RC_FORMAT_SCORE 130 
#define  RC_FORMAT_SECONDS 129 
#define  RC_FORMAT_VALUE 128 
 int snprintf (char*,int,char*,unsigned int,...) ; 

int rc_format_value(char* buffer, int size, unsigned value, int format) {
  unsigned a, b, c;
  int chars;

  switch (format) {
    case RC_FORMAT_FRAMES:
      a = value * 10 / 6; /* centisecs */
      b = a / 100; /* seconds */
      a -= b * 100;
      c = b / 60; /* minutes */
      b -= c * 60;
      chars = snprintf(buffer, size, "%02u:%02u.%02u", c, b, a);
      break;

    case RC_FORMAT_SECONDS:
      a = value / 60; /* minutes */
      value -= a * 60;
      chars = snprintf(buffer, size, "%02u:%02u", a, value);
      break;

    case RC_FORMAT_CENTISECS:
      a = value / 100; /* seconds */
      value -= a * 100;
      b = a / 60; /* minutes */
      a -= b * 60;
      chars = snprintf(buffer, size, "%02u:%02u.%02u", b, a, value);
      break;

    case RC_FORMAT_SCORE:
      chars = snprintf(buffer, size, "%06u Points", value);
      break;

    case RC_FORMAT_VALUE:
      chars = snprintf(buffer, size, "%01u", value);
      break;

    case RC_FORMAT_OTHER:
    default:
      chars = snprintf(buffer, size, "%06u", value);
      break;
  }

  return chars;
}