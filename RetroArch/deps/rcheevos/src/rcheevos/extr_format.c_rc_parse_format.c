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
 int RC_FORMAT_CENTISECS ; 
 int RC_FORMAT_FRAMES ; 
 int RC_FORMAT_OTHER ; 
 int RC_FORMAT_SCORE ; 
 int RC_FORMAT_SECONDS ; 
 int RC_FORMAT_VALUE ; 
 int /*<<< orphan*/  strcmp (char const*,char*) ; 

int rc_parse_format(const char* format_str) {
  switch (*format_str++) {
    case 'F':
      if (!strcmp(format_str, "RAMES")) {
        return RC_FORMAT_FRAMES;
      }

      break;
    
    case 'T':
      if (!strcmp(format_str, "IME")) {
        return RC_FORMAT_FRAMES;
      }
      else if (!strcmp(format_str, "IMESECS")) {
        return RC_FORMAT_SECONDS;
      }

      break;
    
    case 'S':
      if (!strcmp(format_str, "ECS")) {
        return RC_FORMAT_SECONDS;
      }
      if (!strcmp(format_str, "CORE")) {
        return RC_FORMAT_SCORE;
      }

      break;
    
    case 'M':
      if (!strcmp(format_str, "ILLISECS")) {
        return RC_FORMAT_CENTISECS;
      }

      break;

    case 'P':
      if (!strcmp(format_str, "OINTS")) {
        return RC_FORMAT_SCORE;
      }

      break;

    case 'V':
      if (!strcmp(format_str, "ALUE")) {
        return RC_FORMAT_VALUE;
      }

      break;

    case 'O':
      if (!strcmp(format_str, "THER")) {
        return RC_FORMAT_OTHER;
      }

      break;
  }

  return RC_FORMAT_VALUE;
}