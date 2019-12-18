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
typedef  scalar_t__ wchar_t ;

/* Variables and functions */
 int /*<<< orphan*/  MB_CUR_MAX ; 
 int /*<<< orphan*/ * ascii_literal_list ; 
 int mbtowc (scalar_t__*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (char*,char*,int) ; 
 char* stpcpy (char*,int /*<<< orphan*/ ) ; 

int convertNCharToReadable(char *str, int size, char *buf, int bufsize) {
  char *pstr = str;
  char *pbuf = buf;
  // TODO
  wchar_t wc;
  while (size > 0) {
    if (*pstr == '\0') break;
    int byte_width = mbtowc(&wc, pstr, MB_CUR_MAX);

    if ((int)wc < 256) {
      pbuf = stpcpy(pbuf, ascii_literal_list[(int)wc]);
    } else {
      memcpy(pbuf, pstr, byte_width);
      pbuf += byte_width;
    }
    pstr += byte_width;
  }

  *pbuf = '\0';

  return 0;
}