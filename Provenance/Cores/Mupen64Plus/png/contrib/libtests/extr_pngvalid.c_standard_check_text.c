#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* png_const_textp ;
typedef  int /*<<< orphan*/  png_const_structp ;
typedef  char* png_const_charp ;
struct TYPE_3__ {scalar_t__ compression; char* key; char* text; scalar_t__ text_length; scalar_t__ itxt_length; char* lang; char* lang_key; } ;

/* Variables and functions */
 scalar_t__ TEXT_COMPRESSION ; 
 int /*<<< orphan*/  png_error (int /*<<< orphan*/ ,char*) ; 
 size_t safecat (char*,int,size_t,char*) ; 
 int /*<<< orphan*/  sprintf (char*,char*,unsigned long,unsigned long) ; 
 scalar_t__ strcmp (char*,char*) ; 
 scalar_t__ strlen (char*) ; 

__attribute__((used)) static void
standard_check_text(png_const_structp pp, png_const_textp tp,
   png_const_charp keyword, png_const_charp text)
{
   char msg[1024];
   size_t pos = safecat(msg, sizeof msg, 0, "text: ");
   size_t ok;

   pos = safecat(msg, sizeof msg, pos, keyword);
   pos = safecat(msg, sizeof msg, pos, ": ");
   ok = pos;

   if (tp->compression != TEXT_COMPRESSION)
   {
      char buf[64];

      sprintf(buf, "compression [%d->%d], ", TEXT_COMPRESSION,
         tp->compression);
      pos = safecat(msg, sizeof msg, pos, buf);
   }

   if (tp->key == NULL || strcmp(tp->key, keyword) != 0)
   {
      pos = safecat(msg, sizeof msg, pos, "keyword \"");
      if (tp->key != NULL)
      {
         pos = safecat(msg, sizeof msg, pos, tp->key);
         pos = safecat(msg, sizeof msg, pos, "\", ");
      }

      else
         pos = safecat(msg, sizeof msg, pos, "null, ");
   }

   if (tp->text == NULL)
      pos = safecat(msg, sizeof msg, pos, "text lost, ");

   else
   {
      if (tp->text_length != strlen(text))
      {
         char buf[64];
         sprintf(buf, "text length changed[%lu->%lu], ",
            (unsigned long)strlen(text), (unsigned long)tp->text_length);
         pos = safecat(msg, sizeof msg, pos, buf);
      }

      if (strcmp(tp->text, text) != 0)
      {
         pos = safecat(msg, sizeof msg, pos, "text becomes \"");
         pos = safecat(msg, sizeof msg, pos, tp->text);
         pos = safecat(msg, sizeof msg, pos, "\" (was \"");
         pos = safecat(msg, sizeof msg, pos, text);
         pos = safecat(msg, sizeof msg, pos, "\"), ");
      }
   }

   if (tp->itxt_length != 0)
      pos = safecat(msg, sizeof msg, pos, "iTXt length set, ");

   if (tp->lang != NULL)
   {
      pos = safecat(msg, sizeof msg, pos, "iTXt language \"");
      pos = safecat(msg, sizeof msg, pos, tp->lang);
      pos = safecat(msg, sizeof msg, pos, "\", ");
   }

   if (tp->lang_key != NULL)
   {
      pos = safecat(msg, sizeof msg, pos, "iTXt keyword \"");
      pos = safecat(msg, sizeof msg, pos, tp->lang_key);
      pos = safecat(msg, sizeof msg, pos, "\", ");
   }

   if (pos > ok)
   {
      msg[pos-2] = '\0'; /* Remove the ", " at the end */
      png_error(pp, msg);
   }
}