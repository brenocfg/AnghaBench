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
typedef  int /*<<< orphan*/  int64_t ;
typedef  int /*<<< orphan*/  JsonBuf ;

/* Variables and functions */
 int /*<<< orphan*/  httpJsonInt64 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  httpJsonPairHead (int /*<<< orphan*/ *,char*,int) ; 

void httpJsonPairInt64Val(JsonBuf* buf, char* name, int nNameLen, int64_t num) {
  httpJsonPairHead(buf, name, nNameLen);
  httpJsonInt64(buf, num);
}