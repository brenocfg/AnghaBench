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
typedef  int /*<<< orphan*/  httpJsonBuilder ;
typedef  int /*<<< orphan*/  JsonBuf ;

/* Variables and functions */
 int /*<<< orphan*/  httpJsonArray (int /*<<< orphan*/ *,int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  httpJsonPairHead (int /*<<< orphan*/ *,char*,int) ; 

void httpJsonPairArray(JsonBuf* buf, char* name, int len, httpJsonBuilder fnBuilder, void* dsHandle) {
  httpJsonPairHead(buf, name, len);
  httpJsonArray(buf, fnBuilder, dsHandle);
}