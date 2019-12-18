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

/* Variables and functions */
 int /*<<< orphan*/  SEEK_CUR ; 
 int /*<<< orphan*/  UNEXPECTED_ERROR_CODE ; 
 scalar_t__ errno ; 
 scalar_t__ fseek (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stop (struct file*,int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static void
skip_12(struct file *file)
   /* Skip exactly 12 bytes in the input stream - used to skip a CRC and chunk
    * header that has been read before.
    */
{
   /* Since the chunks were read before this shouldn't fail: */
   if (fseek(file->file, 12, SEEK_CUR) != 0)
   {
      if (errno != 0)
         file->read_errno = errno;

      stop(file, UNEXPECTED_ERROR_CODE, "reskip");
   }
}