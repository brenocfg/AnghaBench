#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  size_t int32_t ;
struct TYPE_3__ {size_t n; scalar_t__* z; } ;
typedef  TYPE_1__ SSQLToken ;

/* Variables and functions */
 scalar_t__* TS_PATH_DELIMITER ; 

__attribute__((used)) static bool hasSpecifyDB(SSQLToken* pTableName) {
  for (int32_t i = 0; i < pTableName->n; ++i) {
    if (pTableName->z[i] == TS_PATH_DELIMITER[0]) {
      return true;
    }
  }

  return false;
}