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

/* Variables and functions */
 int TSDB_METER_NAME_LEN ; 

void httpTrimTableName(char *name) {
  for (int i = 0; name[i] != 0; i++) {
    if (name[i] == ' ' || name[i] == ':' || name[i] == '.' || name[i] == '-' || name[i] == '/' || name[i] == '\'')
      name[i] = '_';
    if (i == TSDB_METER_NAME_LEN + 1) {
      name[i] = 0;
      break;
    }
  }
}