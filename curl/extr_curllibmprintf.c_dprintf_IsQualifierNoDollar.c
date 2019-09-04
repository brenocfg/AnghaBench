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
 int FALSE ; 
 int TRUE ; 

__attribute__((used)) static bool dprintf_IsQualifierNoDollar(const char *fmt)
{
#if defined(MP_HAVE_INT_EXTENSIONS)
  if(!strncmp(fmt, "I32", 3) || !strncmp(fmt, "I64", 3)) {
    return TRUE;
  }
#endif

  switch(*fmt) {
  case '-': case '+': case ' ': case '#': case '.':
  case '0': case '1': case '2': case '3': case '4':
  case '5': case '6': case '7': case '8': case '9':
  case 'h': case 'l': case 'L': case 'z': case 'q':
  case '*': case 'O':
#if defined(MP_HAVE_INT_EXTENSIONS)
  case 'I':
#endif
    return TRUE;

  default:
    return FALSE;
  }
}