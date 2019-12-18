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
struct TYPE_5__ {int /*<<< orphan*/  lst; } ;
typedef  TYPE_1__ JsonBuf ;

/* Variables and functions */
 int /*<<< orphan*/  MAX_NUM_STR_SZ ; 
 int /*<<< orphan*/  httpJsonItemToken (TYPE_1__*) ; 
 int /*<<< orphan*/  httpJsonTestBuf (TYPE_1__*,int /*<<< orphan*/ ) ; 
 scalar_t__ snprintf (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,double) ; 

void httpJsonDouble(JsonBuf* buf, double num) {
  httpJsonItemToken(buf);
  httpJsonTestBuf(buf, MAX_NUM_STR_SZ);
  if (num > 1E10 || num < -1E10) {
    buf->lst += snprintf(buf->lst, MAX_NUM_STR_SZ, "%.9e", num);
  } else {
    buf->lst += snprintf(buf->lst, MAX_NUM_STR_SZ, "%.9f", num);
  }
}