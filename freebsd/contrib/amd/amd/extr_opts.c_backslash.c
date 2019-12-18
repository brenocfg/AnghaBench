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
 int /*<<< orphan*/  XLOG_USER ; 
 int /*<<< orphan*/  plog (int /*<<< orphan*/ ,char*,...) ; 

__attribute__((used)) static char
backslash(char **p)
{
  char c;

  if ((*p)[1] == '\0') {
    plog(XLOG_USER, "Empty backslash escape");
    return **p;
  }

  if (**p == '\\') {
    (*p)++;
    switch (**p) {
    case 'g':
      c = '\007';		/* Bell */
      break;
    case 'b':
      c = '\010';		/* Backspace */
      break;
    case 't':
      c = '\011';		/* Horizontal Tab */
      break;
    case 'n':
      c = '\012';		/* New Line */
      break;
    case 'v':
      c = '\013';		/* Vertical Tab */
      break;
    case 'f':
      c = '\014';		/* Form Feed */
      break;
    case 'r':
      c = '\015';		/* Carriage Return */
      break;
    case 'e':
      c = '\033';		/* Escape */
      break;
    case '0':
    case '1':
    case '2':
    case '3':
    case '4':
    case '5':
    case '6':
    case '7':
      {
	int cnt, val, ch;

	for (cnt = 0, val = 0; cnt < 3; cnt++) {
	  ch = *(*p)++;
	  if (ch < '0' || ch > '7') {
	    (*p)--;
	    break;
	  }
	  val = (val << 3) | (ch - '0');
	}

	if ((val & 0xffffff00) != 0)
	  plog(XLOG_USER,
	       "Too large character constant %u\n",
	       val);
	c = (char) val;
	--(*p);
      }
      break;

    default:
      c = **p;
      break;
    }
  } else
    c = **p;

  return c;
}