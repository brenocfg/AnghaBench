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
struct TYPE_5__ {char const* wname; scalar_t__* test; int /*<<< orphan*/ * pwrite; TYPE_1__* current; int /*<<< orphan*/ * pread; } ;
typedef  TYPE_2__ png_store ;
typedef  int /*<<< orphan*/ * png_const_structp ;
struct TYPE_4__ {char const* name; } ;

/* Variables and functions */
 size_t safecat (char*,size_t,size_t,char const*) ; 
 char const* sep ; 

__attribute__((used)) static size_t
store_message(png_store *ps, png_const_structp pp, char *buffer, size_t bufsize,
   size_t pos, const char *msg)
{
   if (pp != NULL && pp == ps->pread)
   {
      /* Reading a file */
      pos = safecat(buffer, bufsize, pos, "read: ");

      if (ps->current != NULL)
      {
         pos = safecat(buffer, bufsize, pos, ps->current->name);
         pos = safecat(buffer, bufsize, pos, sep);
      }
   }

   else if (pp != NULL && pp == ps->pwrite)
   {
      /* Writing a file */
      pos = safecat(buffer, bufsize, pos, "write: ");
      pos = safecat(buffer, bufsize, pos, ps->wname);
      pos = safecat(buffer, bufsize, pos, sep);
   }

   else
   {
      /* Neither reading nor writing (or a memory error in struct delete) */
      pos = safecat(buffer, bufsize, pos, "pngvalid: ");
   }

   if (ps->test[0] != 0)
   {
      pos = safecat(buffer, bufsize, pos, ps->test);
      pos = safecat(buffer, bufsize, pos, sep);
   }
   pos = safecat(buffer, bufsize, pos, msg);
   return pos;
}