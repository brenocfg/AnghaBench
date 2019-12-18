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
typedef  int /*<<< orphan*/  U8 ;

/* Variables and functions */

__attribute__((used)) static U8 *_EncodeStr(U8 *pPayload, const char *pText, unsigned int Limit) {
  unsigned int n;
  unsigned int Len;
  //
  // Compute string len
  //
  Len = 0;
  while(*(pText + Len) != 0) {
    Len++;
  }
  if (Len > Limit) {
    Len = Limit;
  }
  //
  // Write Len
  //
  if (Len < 255)  {
    *pPayload++ = Len; 
  } else {
    *pPayload++ = 255;
    *pPayload++ = (Len & 255);
    *pPayload++ = ((Len >> 8) & 255);
  }
  //
  // copy string
  //
  n = 0;
  while (n < Len) {
    *pPayload++ = *pText++;
    n++;
  }
  return pPayload;
}