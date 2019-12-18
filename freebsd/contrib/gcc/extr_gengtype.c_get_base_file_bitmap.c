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

/* Variables and functions */
 size_t NUM_BASE_FILES ; 
 unsigned int NUM_LANG_FILES ; 
 char* get_file_basename (char const*) ; 
 char const** lang_dir_names ; 
 int /*<<< orphan*/ * lang_files ; 
 int /*<<< orphan*/ * langs_for_lang_files ; 
 scalar_t__ memcmp (char const*,char const*,size_t) ; 
 char* strchr (char const*,char) ; 
 int /*<<< orphan*/  strcmp (char const*,int /*<<< orphan*/ ) ; 
 size_t strlen (char const*) ; 

unsigned
get_base_file_bitmap (const char *input_file)
{
  const char *basename = get_file_basename (input_file);
  const char *slashpos = strchr (basename, '/');
  unsigned j;
  unsigned k;
  unsigned bitmap;

  /* If the file resides in a language subdirectory (e.g., 'cp'), assume that
     it belongs to the corresponding language.  The file may belong to other
     languages as well (which is checked for below).  */

  if (slashpos)
    {
      size_t i;
      for (i = 1; i < NUM_BASE_FILES; i++)
	if ((size_t)(slashpos - basename) == strlen (lang_dir_names [i])
	    && memcmp (basename, lang_dir_names[i], strlen (lang_dir_names[i])) == 0)
          {
            /* It's in a language directory, set that language.  */
            bitmap = 1 << i;
          }
    }

  /* If it's in any config-lang.in, then set for the languages
     specified.  */

  bitmap = 0;

  for (j = 0; j < NUM_LANG_FILES; j++)
    {
      if (!strcmp(input_file, lang_files[j]))
        {
          for (k = 0; k < NUM_BASE_FILES; k++)
            {
              if (!strcmp(lang_dir_names[k], langs_for_lang_files[j]))
                bitmap |= (1 << k);
            }
        }
    }

  /* Otherwise, set all languages.  */
  if (!bitmap)
    bitmap = (1 << NUM_BASE_FILES) - 1;

  return bitmap;
}