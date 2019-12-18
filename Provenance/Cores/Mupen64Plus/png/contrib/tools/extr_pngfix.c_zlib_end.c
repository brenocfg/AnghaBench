#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {char* msg; } ;
struct zlib {int ok_bits; int file_bits; scalar_t__ state; scalar_t__ rc; TYPE_4__ z; TYPE_3__* file; int /*<<< orphan*/  compressed_digits; int /*<<< orphan*/  compressed_bytes; TYPE_2__* chunk; int /*<<< orphan*/  uncompressed_digits; int /*<<< orphan*/  uncompressed_bytes; scalar_t__ cksum; TYPE_1__* global; } ;
struct TYPE_7__ {int /*<<< orphan*/  file_name; } ;
struct TYPE_6__ {int /*<<< orphan*/  chunk_type; } ;
struct TYPE_5__ {int /*<<< orphan*/  quiet; } ;

/* Variables and functions */
 int /*<<< orphan*/  CLEAR (struct zlib) ; 
 scalar_t__ Z_OK ; 
 int /*<<< orphan*/  emit_string (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fputs (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ inflateEnd (TYPE_4__*) ; 
 int /*<<< orphan*/  printf (char*,char const*,...) ; 
 int /*<<< orphan*/  putc (char,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stdout ; 
 int /*<<< orphan*/  type_name (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uarb_print (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 char* zlib_flevel (struct zlib*) ; 
 int /*<<< orphan*/  zlib_message (struct zlib*,int) ; 
 char* zlib_rc (struct zlib*) ; 

__attribute__((used)) static void
zlib_end(struct zlib *zlib)
{
   /* Output the summary line now; this ensures a summary line always gets
    * output regardless of the manner of exit.
    */
   if (!zlib->global->quiet)
   {
      if (zlib->ok_bits < 16) /* stream was read ok */
      {
         const char *reason;

         if (zlib->cksum)
            reason = "CHK"; /* checksum error */

         else if (zlib->ok_bits > zlib->file_bits)
            reason = "TFB"; /* fixing a too-far-back error */

         else if (zlib->ok_bits == zlib->file_bits)
            reason = "OK ";

         else
            reason = "OPT"; /* optimizing window bits */

         /* SUMMARY FORMAT (for a successful zlib inflate):
          *
          * IDAT reason flevel file-bits ok-bits compressed uncompressed file
          */
         type_name(zlib->chunk->chunk_type, stdout);
         printf(" %s %s %d %d ", reason, zlib_flevel(zlib), zlib->file_bits,
            zlib->ok_bits);
         uarb_print(zlib->compressed_bytes, zlib->compressed_digits, stdout);
         putc(' ', stdout);
         uarb_print(zlib->uncompressed_bytes, zlib->uncompressed_digits,
            stdout);
         putc(' ', stdout);
         fputs(zlib->file->file_name, stdout);
         putc('\n', stdout);
      }

      else
      {
         /* This is a zlib read error; the chunk will be skipped.  For an IDAT
          * stream this will also cause a fatal read error (via stop()).
          *
          * SUMMARY FORMAT:
          *
          * IDAT SKP flevel file-bits z-rc compressed message file
          *
          * z-rc is the zlib failure code; message is the error message with
          * spaces replaced by '-'.  The compressed byte count indicates where
          * in the zlib stream the error occurred.
          */
         type_name(zlib->chunk->chunk_type, stdout);
         printf(" SKP %s %d %s ", zlib_flevel(zlib), zlib->file_bits,
            zlib_rc(zlib));
         uarb_print(zlib->compressed_bytes, zlib->compressed_digits, stdout);
         putc(' ', stdout);
         emit_string(zlib->z.msg ? zlib->z.msg : "[no_message]", stdout);
         putc(' ', stdout);
         fputs(zlib->file->file_name, stdout);
         putc('\n', stdout);
      }
   }

   if (zlib->state >= 0)
   {
      zlib->rc = inflateEnd(&zlib->z);

      if (zlib->rc != Z_OK)
         zlib_message(zlib, 1/*unexpected*/);
   }

   CLEAR(*zlib);
}