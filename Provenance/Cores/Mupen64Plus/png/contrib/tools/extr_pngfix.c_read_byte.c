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
struct file {int /*<<< orphan*/  status_code; scalar_t__ read_errno; int /*<<< orphan*/  file; int /*<<< orphan*/  read_count; } ;

/* Variables and functions */
 scalar_t__ EDOM ; 
 scalar_t__ EINTR ; 
 int EOF ; 
 scalar_t__ ERANGE ; 
 int /*<<< orphan*/  INTERNAL_ERROR ; 
 int /*<<< orphan*/  TRUNCATED ; 
 int /*<<< orphan*/  UNEXPECTED_ERROR_CODE ; 
 int /*<<< orphan*/  emit_error (struct file*,int /*<<< orphan*/ ,char*) ; 
 scalar_t__ errno ; 
 scalar_t__ feof (int /*<<< orphan*/ ) ; 
 scalar_t__ ferror (int /*<<< orphan*/ ) ; 
 int getc (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
read_byte(struct file *file)
{
   int ch = getc(file->file);

   if (ch >= 0 && ch <= 255)
   {
      ++(file->read_count);
      return ch;
   }

   else if (ch != EOF)
   {
      file->status_code |= INTERNAL_ERROR;
      file->read_errno = ERANGE; /* out of range character */

      /* This is very unexpected; an error message is always output: */
      emit_error(file, UNEXPECTED_ERROR_CODE, "file read");
   }

#  ifdef EINTR
      else if (errno == EINTR) /* Interrupted, try again */
      {
         errno = 0;
         return read_byte(file);
      }
#  endif

   else
   {
      /* An error, it doesn't really matter what the error is but it gets
       * recorded anyway.
       */
      if (ferror(file->file))
         file->read_errno = errno;

      else if (feof(file->file))
         file->read_errno = 0; /* I.e. a regular EOF, no error */

      else /* unexpected */
         file->read_errno = EDOM;
   }

   /* 'TRUNCATED' is used for all cases of failure to read a byte, because of
    * the way libpng works a byte read is never attempted unless the byte is
    * expected to be there, so EOF should not occur.
    */
   file->status_code |= TRUNCATED;
   return EOF;
}