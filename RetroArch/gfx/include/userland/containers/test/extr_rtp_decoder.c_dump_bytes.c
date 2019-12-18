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
typedef  int /*<<< orphan*/  uint8_t ;

/* Variables and functions */
 int BYTES_PER_ROW ; 
 int /*<<< orphan*/  LOG_INFO (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  sprintf (char*,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void dump_bytes(const uint8_t *buffer, size_t buffer_len)
{
   char dump_str[3 * BYTES_PER_ROW + 1];
   int in_row = 0;

   while (buffer_len--)
   {
      sprintf(dump_str + 3 * in_row, "%2.2X ", *buffer++);
      if (++in_row == BYTES_PER_ROW)
      {
         LOG_INFO(NULL, dump_str);
         in_row = 0;
      }
   }

   if (in_row)
   {
      LOG_INFO(NULL, dump_str);
   }
}