#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {char* pos; } ;
struct TYPE_5__ {char* buffer; int bufsize; TYPE_1__ data; } ;
typedef  TYPE_2__ HttpParser ;
typedef  int /*<<< orphan*/  HttpContext ;

/* Variables and functions */
 int /*<<< orphan*/  memmove (char*,char*,size_t) ; 
 char* strstr (char*,char*) ; 
 size_t strtoul (char*,int /*<<< orphan*/ *,int) ; 

bool httpParseChunkedBody(HttpContext* pContext, HttpParser* pParser, bool test) {
  char*  pEnd = pParser->buffer + pParser->bufsize;
  char*  pRet = pParser->data.pos;
  char*  pSize = pParser->data.pos;
  size_t size = strtoul(pSize, NULL, 16);
  if (size <= 0) return false;

  while (size > 0) {
    char* pData = strstr(pSize, "\r\n");
    if (pData == NULL || pData >= pEnd) return false;
    pData += 2;

    pSize = strstr(pData, "\r\n");
    if (pSize == NULL || pSize >= pEnd) return false;
    if ((size_t)(pSize - pData) != size) return false;
    pSize += 2;

    if (!test) {
      memmove(pRet, pData, size);
      pRet += size;
    }

    size = strtoul(pSize, NULL, 16);
  }

  if (!test) {
    *pRet = '\0';
  }

  return true;
}