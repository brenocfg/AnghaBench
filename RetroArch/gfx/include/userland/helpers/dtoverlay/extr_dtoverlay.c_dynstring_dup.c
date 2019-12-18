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
struct dynstring {int len; int /*<<< orphan*/  buf; } ;

/* Variables and functions */
 int dynstring_set_size (struct dynstring*,int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,char const*,int) ; 
 int strlen (char const*) ; 

__attribute__((used)) static int dynstring_dup(struct dynstring *ds, const char *src, int len)
{
   int err = 0;

   if (!len)
      len = strlen(src);

   err = dynstring_set_size(ds, len + 1);
   if (!err)
   {
      memcpy(ds->buf, src, len + 1);
      ds->len = len;
   }

   return err;
}