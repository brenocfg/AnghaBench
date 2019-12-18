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
typedef  size_t int32_t ;

/* Variables and functions */
 int /*<<< orphan*/  printf (char*,...) ; 

__attribute__((used)) static void printBinaryData(char *data, int32_t len) {
  bool isCharString = true;
  for (int32_t i = 0; i < len; ++i) {
    if ((data[i] <= 'Z' && data[i] >= 'A') || (data[i] <= 'z' && data[i] >= 'a') ||
        (data[i] >= '0' && data[i] <= '9')) {
      continue;
    } else if (data[i] == 0) {
      break;
    } else {
      isCharString = false;
      break;
    }
  }

  if (len == 50) {  // probably the avg intermediate result
    printf("%lf,%d\t", *(double *)data, *(int64_t *)(data + sizeof(double)));
  } else if (data[8] == ',') {  // in TSDB_FUNC_FIRST_DST/TSDB_FUNC_LAST_DST,
                                // the value is seperated by ','
    printf("%ld,%0x\t", *(int64_t *)data, data + sizeof(int64_t) + 1);
  } else if (isCharString) {
    printf("%s\t", data);
  }
}