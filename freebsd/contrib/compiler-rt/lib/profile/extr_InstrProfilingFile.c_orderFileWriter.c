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
typedef  int uint32_t ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 scalar_t__ INSTR_ORDER_FILE_BUFFER_SIZE ; 
 scalar_t__ fwrite (int const*,int,scalar_t__,int /*<<< orphan*/ *) ; 

__attribute__((used)) static uint32_t orderFileWriter(FILE *File, const uint32_t *DataStart) {
  if (fwrite(DataStart, sizeof(uint32_t), INSTR_ORDER_FILE_BUFFER_SIZE, File) !=
      INSTR_ORDER_FILE_BUFFER_SIZE)
    return 1;
  return 0;
}