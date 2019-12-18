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
struct dynstring {int len; scalar_t__ buf; } ;

/* Variables and functions */
 int dynstring_set_size (struct dynstring*,int) ; 
 int /*<<< orphan*/  memcpy (scalar_t__,char const*,int) ; 
 int /*<<< orphan*/  memmove (scalar_t__,scalar_t__,int) ; 

__attribute__((used)) static int dynstring_patch(struct dynstring *ds, int pos, int width,
                           const char *src, int len)
{
   int newlen = ds->len + (len - width);
   int err = dynstring_set_size(ds, newlen + 1);
   if (!err)
   {
      if (width != len)
      {
         // Move any data following the patch
         memmove(ds->buf + pos + len, ds->buf + pos + width,
                 ds->len + 1 - (pos + width));
         ds->len = newlen;
      }
      memcpy(ds->buf + pos, src, len);
   }
   return err;
}