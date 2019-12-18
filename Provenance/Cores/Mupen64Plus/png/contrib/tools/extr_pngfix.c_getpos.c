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
struct file {int /*<<< orphan*/  data_pos; } ;

/* Variables and functions */
 int /*<<< orphan*/  file_getpos (struct file*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
getpos(struct file *file)
   /* Get the current position and store it in 'data_pos'.  The corresponding
    * setpos() function is chunk specific because it uses the copy of the
    * position for the specific chunk.
    */
{
   file_getpos(file, &file->data_pos);
}