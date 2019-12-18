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
typedef  int /*<<< orphan*/  JsonBuf ;

/* Variables and functions */
 int /*<<< orphan*/  JsonStrEnd ; 
 int /*<<< orphan*/  JsonStrStt ; 
 int /*<<< orphan*/  httpJsonItemToken (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  httpJsonPrint (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  httpJsonToken (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void httpJsonStringForTransMean(JsonBuf* buf, char* sVal, int maxLen) {
  httpJsonItemToken(buf);
  httpJsonToken(buf, JsonStrStt);

  if (sVal != NULL) {
    // dispose transferred meaning byte
    char* lastPos = sVal;
    char* curPos = sVal;

    for (int i = 0; i < maxLen; ++i) {
      if (*curPos == 0) {
        break;
      }

      if (*curPos == '\"') {
        httpJsonPrint(buf, lastPos, (int)(curPos - lastPos));
        curPos++;
        lastPos = curPos;
        httpJsonPrint(buf, "\\\"", 2);
      } else if (*curPos == '\\') {
        httpJsonPrint(buf, lastPos, (int)(curPos - lastPos));
        curPos++;
        lastPos = curPos;
        httpJsonPrint(buf, "\\\\", 2);
      } else {
        curPos++;
      }
    }

    if (*lastPos) {
      httpJsonPrint(buf, lastPos, (int)(curPos - lastPos));
    }
  }

  httpJsonToken(buf, JsonStrEnd);
}