#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  int64_t ;
struct TYPE_5__ {int /*<<< orphan*/  lst; } ;
typedef  TYPE_1__ JsonBuf ;

/* Variables and functions */
 int /*<<< orphan*/  MAX_NUM_STR_SZ ; 
 int /*<<< orphan*/  httpJsonItemToken (TYPE_1__*) ; 
 int /*<<< orphan*/  httpJsonTestBuf (TYPE_1__*,int /*<<< orphan*/ ) ; 
 scalar_t__ snprintf (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 

void httpJsonInt64(JsonBuf* buf, int64_t num) {
  httpJsonItemToken(buf);
  httpJsonTestBuf(buf, MAX_NUM_STR_SZ);
  buf->lst += snprintf(buf->lst, MAX_NUM_STR_SZ, "%ld", num);
}