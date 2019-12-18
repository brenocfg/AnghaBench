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
struct file {int /*<<< orphan*/  file_name; int /*<<< orphan*/  file; } ;
typedef  int /*<<< orphan*/  fpos_t ;

/* Variables and functions */
 int /*<<< orphan*/  READ_ERROR_CODE ; 
 scalar_t__ fsetpos (int /*<<< orphan*/ ,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  perror (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stop (struct file*,int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static void
file_setpos(struct file *file, const fpos_t *pos)
{
   if (fsetpos(file->file, pos))
   {
      perror(file->file_name);
      stop(file, READ_ERROR_CODE, "fsetpos");
   }
}