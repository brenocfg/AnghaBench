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
struct file {scalar_t__ read_errno; int /*<<< orphan*/  file; } ;
typedef  int /*<<< orphan*/  png_byte ;

/* Variables and functions */
 int /*<<< orphan*/  UNEXPECTED_ERROR_CODE ; 
 scalar_t__ errno ; 
 int getc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stop (struct file*,int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static png_byte
reread_byte(struct file *file)
   /* Read a byte when an error is not expected to happen because the byte has
    * been read before without error.
    */
{
   int ch = getc(file->file);

   if (errno != 0)
      file->read_errno = errno;

   if (ch < 0 || ch > 255)
      stop(file, UNEXPECTED_ERROR_CODE, "reread");

   return (png_byte)ch;
}