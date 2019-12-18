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
typedef  int /*<<< orphan*/  int8_t ;
typedef  int /*<<< orphan*/  int64_t ;
typedef  int /*<<< orphan*/  int32_t ;
typedef  int /*<<< orphan*/  int16_t ;

/* Variables and functions */
 int /*<<< orphan*/  printf (char*,int) ; 

int checkVersion() {
  if (sizeof(int8_t) != 1) {
    printf("taos int8 size is %d(!= 1)", (int)sizeof(int8_t));
    return 0;
  }
  if (sizeof(int16_t) != 2) {
    printf("taos int16 size is %d(!= 2)", (int)sizeof(int16_t));
    return 0;
  }
  if (sizeof(int32_t) != 4) {
    printf("taos int32 size is %d(!= 4)", (int)sizeof(int32_t));
    return 0;
  }
  if (sizeof(int64_t) != 8) {
    printf("taos int64 size is %d(!= 8)", (int)sizeof(int64_t));
    return 0;
  }
  return 1;
}