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
struct file {int /*<<< orphan*/  write_count; int /*<<< orphan*/  status_code; int /*<<< orphan*/  write_errno; int /*<<< orphan*/ * out; } ;

/* Variables and functions */
 int /*<<< orphan*/  WRITE_ERROR ; 
 int /*<<< orphan*/  WRITE_ERROR_CODE ; 
 int /*<<< orphan*/  errno ; 
 int putc (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stop (struct file*,int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static void
write_byte(struct file *file, int b)
   /* Write one byte to the output - this causes a fatal error if the write
    * fails and the read of this PNG file immediately terminates.  Just
    * increments the write count if there is no output file.
    */
{
   if (file->out != NULL)
   {
      if (putc(b, file->out) != b)
      {
         file->write_errno = errno;
         file->status_code |= WRITE_ERROR;
         stop(file, WRITE_ERROR_CODE, "write byte");
      }
   }

   ++(file->write_count);
}