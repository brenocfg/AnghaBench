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
struct TYPE_5__ {char* name; } ;

/* Variables and functions */
 TYPE_2__* chunk_info ; 
 int find_by_flag (int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*,char*,char*,char const*) ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static void
check_error(display *d, png_uint_32 flags, const char *message)
{
   while (flags)
   {
      png_uint_32 flag = flags & -(png_int_32)flags;
      int i = find_by_flag(flag);

      fprintf(stderr, "%s(%s): chunk %s: %s\n", d->file, d->test,
         chunk_info[i].name, message);
      ++(d->error_count);

      flags &= ~flag;
   }
}