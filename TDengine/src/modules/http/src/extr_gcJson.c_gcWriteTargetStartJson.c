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
 int /*<<< orphan*/  JsonArrStt ; 
 int /*<<< orphan*/  JsonObjStt ; 
 int /*<<< orphan*/  httpJsonItemToken (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  httpJsonPair (int /*<<< orphan*/ *,char*,int,char*,int) ; 
 int /*<<< orphan*/  httpJsonPairHead (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  httpJsonToken (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ strlen (char*) ; 

void gcWriteTargetStartJson(JsonBuf *jsonBuf, char *refId, char *target) {
  if (strlen(target) == 0) {
    target = refId;
  }

  // object begin
  httpJsonItemToken(jsonBuf);
  httpJsonToken(jsonBuf, JsonObjStt);

  // target section
  httpJsonPair(jsonBuf, "refId", 5, refId, (int)strlen(refId));
  httpJsonPair(jsonBuf, "target", 6, target, (int)strlen(target));

  // data begin
  httpJsonPairHead(jsonBuf, "datapoints", 10);

  // data array begin
  httpJsonToken(jsonBuf, JsonArrStt);
}