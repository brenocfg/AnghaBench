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
struct file_data {int eof; scalar_t__ buffered; int /*<<< orphan*/  name; int /*<<< orphan*/  desc; } ;

/* Variables and functions */
 scalar_t__ FILE_BUFFER (struct file_data*) ; 
 size_t SIZE_MAX ; 
 size_t block_read (int /*<<< orphan*/ ,scalar_t__,size_t) ; 
 int /*<<< orphan*/  pfatal_with_name (int /*<<< orphan*/ ) ; 

void
file_block_read (struct file_data *current, size_t size)
{
  if (size && ! current->eof)
    {
      size_t s = block_read (current->desc,
			     FILE_BUFFER (current) + current->buffered, size);
      if (s == SIZE_MAX)
	pfatal_with_name (current->name);
      current->buffered += s;
      current->eof = s < size;
    }
}