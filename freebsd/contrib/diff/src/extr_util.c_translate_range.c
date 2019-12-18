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
struct file_data {int dummy; } ;
typedef  scalar_t__ lin ;

/* Variables and functions */
 int translate_line_number (struct file_data const*,scalar_t__) ; 

void
translate_range (struct file_data const *file,
		 lin a, lin b,
		 long int *aptr, long int *bptr)
{
  *aptr = translate_line_number (file, a - 1) + 1;
  *bptr = translate_line_number (file, b + 1) - 1;
}