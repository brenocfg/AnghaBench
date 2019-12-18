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
 int /*<<< orphan*/  httpJsonOriginString (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  httpJsonPairHead (int /*<<< orphan*/ *,char*,int) ; 

void httpJsonPairOriginString(JsonBuf* buf, char* name, int nameLen, char* sVal, int valLen) {
  httpJsonPairHead(buf, name, nameLen);
  httpJsonOriginString(buf, sVal, valLen);
}