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
struct file {int read_errno; int write_errno; char* file_name; } ;

/* Variables and functions */
#define  INVALID_ERROR_CODE 134 
#define  LIBPNG_ERROR_CODE 133 
#define  LIBPNG_WARNING_CODE 132 
#define  READ_ERROR_CODE 131 
#define  UNEXPECTED_ERROR_CODE 130 
#define  WRITE_ERROR_CODE 129 
#define  ZLIB_ERROR_CODE 128 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*,char const*,char const*,...) ; 
 int /*<<< orphan*/  stderr ; 
 char* strerror (int) ; 

__attribute__((used)) static void
emit_error(struct file *file, int code, const char *what)
   /* Generic error message routine, takes a 'stop' code but can be used
    * elsewhere.  Always outputs a message.
    */
{
   const char *reason;
   int err = 0;

   switch (code)
   {
      case LIBPNG_WARNING_CODE:   reason = "libpng warning:"; break;
      case LIBPNG_ERROR_CODE:     reason = "libpng error:"; break;
      case ZLIB_ERROR_CODE:       reason = "zlib error:"; break;
      case INVALID_ERROR_CODE:    reason = "invalid"; break;
      case READ_ERROR_CODE:       reason = "read failure:";
                                  err = file->read_errno;
                                  break;
      case WRITE_ERROR_CODE:      reason = "write error";
                                  err = file->write_errno;
                                  break;
      case UNEXPECTED_ERROR_CODE: reason = "unexpected error:";
                                  err = file->read_errno;
                                  if (err == 0)
                                     err = file->write_errno;
                                  break;
      default:                    reason = "INVALID (internal error):"; break;
   }

   if (err != 0)
      fprintf(stderr, "%s: %s %s [%s]\n", file->file_name, reason, what,
         strerror(err));

   else
      fprintf(stderr, "%s: %s %s\n", file->file_name, reason, what);
}