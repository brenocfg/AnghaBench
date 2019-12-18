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
typedef  scalar_t__ uint64_t ;
typedef  int /*<<< orphan*/  data ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int fread (scalar_t__*,int,int,int /*<<< orphan*/ *) ; 

uint64_t mgmtGetCheckSum(FILE* fp, int offset) {
  uint64_t checksum = 0;
  uint64_t data;
  int      bytes;

  while (1) {
    data = 0;
    bytes = fread(&data, sizeof(data), 1, fp);

    if (bytes != sizeof(data)) break;

    checksum += data;
  }

  return checksum;
}