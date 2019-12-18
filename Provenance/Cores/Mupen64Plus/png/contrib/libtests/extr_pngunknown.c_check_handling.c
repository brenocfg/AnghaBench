#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int png_uint_32 ;
typedef  int png_int_32 ;
struct TYPE_4__ {char* file; char* test; int /*<<< orphan*/  error_count; } ;
typedef  TYPE_1__ display ;
struct TYPE_5__ {int keep; char* name; scalar_t__ unknown; } ;

/* Variables and functions */
#define  PNG_HANDLE_CHUNK_ALWAYS 131 
#define  PNG_HANDLE_CHUNK_AS_DEFAULT 130 
#define  PNG_HANDLE_CHUNK_IF_SAFE 129 
#define  PNG_HANDLE_CHUNK_NEVER 128 
 int /*<<< orphan*/  ancillary (char*) ; 
 TYPE_2__* chunk_info ; 
 int find_by_flag (int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*,char*,char*,char const*,char*,char const*,char const*) ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static void
check_handling(display *d, int def, png_uint_32 chunks, png_uint_32 known,
   png_uint_32 unknown, const char *position, int set_callback)
{
   while (chunks)
   {
      png_uint_32 flag = chunks & -(png_int_32)chunks;
      int i = find_by_flag(flag);
      int keep = chunk_info[i].keep;
      const char *type;
      const char *errorx = NULL;

      if (chunk_info[i].unknown)
      {
         if (keep == PNG_HANDLE_CHUNK_AS_DEFAULT)
         {
            type = "UNKNOWN (default)";
            keep = def;
         }

         else
            type = "UNKNOWN (specified)";

         if (flag & known)
            errorx = "chunk processed";

         else switch (keep)
         {
            case PNG_HANDLE_CHUNK_AS_DEFAULT:
               if (flag & unknown)
                  errorx = "DEFAULT: unknown chunk saved";
               break;

            case PNG_HANDLE_CHUNK_NEVER:
               if (flag & unknown)
                  errorx = "DISCARD: unknown chunk saved";
               break;

            case PNG_HANDLE_CHUNK_IF_SAFE:
               if (ancillary(chunk_info[i].name))
               {
                  if (!(flag & unknown))
                     errorx = "IF-SAFE: unknown ancillary chunk lost";
               }

               else if (flag & unknown)
                  errorx = "IF-SAFE: unknown critical chunk saved";
               break;

            case PNG_HANDLE_CHUNK_ALWAYS:
               if (!(flag & unknown))
                  errorx = "SAVE: unknown chunk lost";
               break;

            default:
               errorx = "internal error: bad keep";
               break;
         }
      } /* unknown chunk */

      else /* known chunk */
      {
         type = "KNOWN";

         if (flag & known)
         {
            /* chunk was processed, it won't have been saved because that is
             * caught below when checking for inconsistent processing.
             */
            if (keep != PNG_HANDLE_CHUNK_AS_DEFAULT)
               errorx = "!DEFAULT: known chunk processed";
         }

         else /* not processed */ switch (keep)
         {
            case PNG_HANDLE_CHUNK_AS_DEFAULT:
               errorx = "DEFAULT: known chunk not processed";
               break;

            case PNG_HANDLE_CHUNK_NEVER:
               if (flag & unknown)
                  errorx = "DISCARD: known chunk saved";
               break;

            case PNG_HANDLE_CHUNK_IF_SAFE:
               if (ancillary(chunk_info[i].name))
               {
                  if (!(flag & unknown))
                     errorx = "IF-SAFE: known ancillary chunk lost";
               }

               else if (flag & unknown)
                  errorx = "IF-SAFE: known critical chunk saved";
               break;

            case PNG_HANDLE_CHUNK_ALWAYS:
               if (!(flag & unknown))
                  errorx = "SAVE: known chunk lost";
               break;

            default:
               errorx = "internal error: bad keep (2)";
               break;
         }
      }

      if (errorx != NULL)
      {
         ++(d->error_count);
         fprintf(stderr, "%s(%s%s): %s %s %s: %s\n", d->file, d->test,
            set_callback ? ",callback" : "",
            type, chunk_info[i].name, position, errorx);
      }

      chunks &= ~flag;
   }
}