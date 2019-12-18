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
struct playlist_entry {char* label; char* path; } ;

/* Variables and functions */
 int PATH_MAX_LENGTH ; 
 scalar_t__ calloc (int,int) ; 
 int /*<<< orphan*/  fill_short_pathname_representation (char*,char*,int) ; 
 int /*<<< orphan*/  free (char*) ; 
 int strcasecmp (char*,char*) ; 
 scalar_t__ string_is_empty (char*) ; 

__attribute__((used)) static int playlist_qsort_func(const struct playlist_entry *a,
      const struct playlist_entry *b)
{
   char *a_str            = NULL;
   char *b_str            = NULL;
   char *a_fallback_label = NULL;
   char *b_fallback_label = NULL;
   int ret                = 0;

   if (!a || !b)
      goto end;

   a_str                  = a->label;
   b_str                  = b->label;

   /* It is quite possible for playlist labels
    * to be blank. If that is the case, have to use
    * filename as a fallback (this is slow, but we
    * have no other option...) */
   if (string_is_empty(a_str))
   {
      if (string_is_empty(a->path))
         goto end;

      a_fallback_label = (char*)calloc(PATH_MAX_LENGTH, sizeof(char));

      if (!a_fallback_label)
         goto end;

      fill_short_pathname_representation(a_fallback_label, a->path, PATH_MAX_LENGTH * sizeof(char));

      if (string_is_empty(a_fallback_label))
         goto end;

      a_str = a_fallback_label;
   }

   if (string_is_empty(b_str))
   {
      if (string_is_empty(b->path))
         goto end;

      b_fallback_label = (char*)calloc(PATH_MAX_LENGTH, sizeof(char));

      if (!b_fallback_label)
         goto end;

      fill_short_pathname_representation(b_fallback_label, b->path, PATH_MAX_LENGTH * sizeof(char));

      if (string_is_empty(b_fallback_label))
         goto end;

      b_str = b_fallback_label;
   }

   ret = strcasecmp(a_str, b_str);

end:

   a_str = NULL;
   b_str = NULL;

   if (a_fallback_label)
   {
      free(a_fallback_label);
      a_fallback_label = NULL;
   }

   if (b_fallback_label)
   {
      free(b_fallback_label);
      b_fallback_label = NULL;
   }

   return ret;
}