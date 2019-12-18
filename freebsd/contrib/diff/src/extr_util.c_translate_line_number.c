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
struct file_data {scalar_t__ prefix_lines; } ;
typedef  scalar_t__ lin ;

/* Variables and functions */

lin
translate_line_number (struct file_data const *file, lin i)
{
  return i + file->prefix_lines + 1;
}