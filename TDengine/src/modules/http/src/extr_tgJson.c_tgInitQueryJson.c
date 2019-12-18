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
typedef  int /*<<< orphan*/  HttpContext ;

/* Variables and functions */
 int /*<<< orphan*/  JsonArrStt ; 
 int /*<<< orphan*/  JsonObjStt ; 
 int /*<<< orphan*/  httpInitJsonBuf (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  httpJsonItemToken (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  httpJsonPairHead (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  httpJsonToken (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * httpMallocJsonBuf (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  httpWriteJsonBufHead (int /*<<< orphan*/ *) ; 

void tgInitQueryJson(HttpContext *pContext) {
  JsonBuf *jsonBuf = httpMallocJsonBuf(pContext);
  if (jsonBuf == NULL) return;

  httpInitJsonBuf(jsonBuf, pContext);
  httpWriteJsonBufHead(jsonBuf);

  // array begin
  httpJsonItemToken(jsonBuf);
  httpJsonToken(jsonBuf, JsonObjStt);

  httpJsonPairHead(jsonBuf, "metrics", 7);

  httpJsonItemToken(jsonBuf);
  httpJsonToken(jsonBuf, JsonArrStt);
}