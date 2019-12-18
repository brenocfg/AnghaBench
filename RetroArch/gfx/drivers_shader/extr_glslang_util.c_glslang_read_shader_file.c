#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
union string_list_elem_attr {int /*<<< orphan*/  i; } ;
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  tmp ;
struct string_list {int size; TYPE_1__* elems; } ;
typedef  scalar_t__ int64_t ;
typedef  int /*<<< orphan*/  include_path ;
typedef  int /*<<< orphan*/  include_file ;
struct TYPE_2__ {char* data; } ;

/* Variables and functions */
 int PATH_MAX_LENGTH ; 
 int /*<<< orphan*/  RARCH_ERR (char*,...) ; 
 int /*<<< orphan*/  STRLEN_CONST (char*) ; 
 int /*<<< orphan*/  filestream_read_file (char const*,void**,scalar_t__*) ; 
 int /*<<< orphan*/  fill_pathname_resolve_relative (char*,char const*,char*,int) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  get_include_file (char const*,char*,int) ; 
 char* path_basename (char const*) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,unsigned int,char const*) ; 
 scalar_t__ string_is_empty (char const*) ; 
 int /*<<< orphan*/  string_list_append (struct string_list*,char const*,union string_list_elem_attr) ; 
 int /*<<< orphan*/  string_list_free (struct string_list*) ; 
 int /*<<< orphan*/  string_remove_all_chars (char*,char) ; 
 struct string_list* string_separate (char*,char*) ; 
 scalar_t__ strncmp (char*,char const*,int /*<<< orphan*/ ) ; 

bool glslang_read_shader_file(const char *path,
      struct string_list *output, bool root_file)
{
   char tmp[PATH_MAX_LENGTH];
   union string_list_elem_attr attr;
   size_t i;
   const char *basename      = NULL;
   uint8_t *buf              = NULL;
   int64_t buf_len           = 0;
   struct string_list *lines = NULL;

   tmp[0] = '\0';
   attr.i = 0;

   /* Sanity check */
   if (string_is_empty(path) || !output)
      return false;

   basename      = path_basename(path);

   if (string_is_empty(basename))
      return false;

   /* Read file contents */
   if (!filestream_read_file(path, (void**)&buf, &buf_len))
   {
      RARCH_ERR("Failed to open shader file: \"%s\".\n", path);
      return false;
   }

   if (buf_len > 0)
   {
      /* Remove Windows '\r' chars if we encounter them */
      string_remove_all_chars((char*)buf, '\r');

      /* Split into lines
       * (Blank lines must be included) */
      lines = string_separate((char*)buf, "\n");
   }

   /* Buffer is no longer required - clean up */
   if (buf)
      free(buf);

   /* Sanity check */
   if (!lines)
      return false;

   if (lines->size < 1)
      goto error;

   /* If this is the 'parent' shader file, ensure that first
    * line is a 'VERSION' string */
   if (root_file)
   {
      const char *line = lines->elems[0].data;

      if (strncmp("#version ", line, STRLEN_CONST("#version ")))
      {
         RARCH_ERR("First line of the shader must contain a valid #version string.\n");
         goto error;
      }

      if (!string_list_append(output, line, attr))
         goto error;

      /* Allows us to use #line to make dealing with shader errors easier.
       * This is supported by glslang, but since we always use glslang statically,
       * this is fine. */

      if (!string_list_append(output, "#extension GL_GOOGLE_cpp_style_line_directive : require", attr))
         goto error;
   }

   /* At least VIM treats the first line as line #1,
    * so offset everything by one. */
   snprintf(tmp, sizeof(tmp), "#line %u \"%s\"", root_file ? 2 : 1, basename);
   if (!string_list_append(output, tmp, attr))
      goto error;

   /* Loop through lines of file */
   for (i = root_file ? 1 : 0; i < lines->size; i++)
   {
      unsigned push_line = 0;
      const char *line   = lines->elems[i].data;

      /* Check for 'include' statements */
      if (!strncmp("#include ", line, STRLEN_CONST("#include ")))
      {
         char include_file[PATH_MAX_LENGTH];
         char include_path[PATH_MAX_LENGTH];

         include_file[0] = '\0';
         include_path[0] = '\0';

         /* Build include file path */
         get_include_file(line, include_file, sizeof(include_file));

         if (string_is_empty(include_file))
         {
            RARCH_ERR("Invalid include statement \"%s\".\n", line);
            goto error;
         }

         fill_pathname_resolve_relative(
               include_path, path, include_file, sizeof(include_path));

         /* Parse include file */
         if (!glslang_read_shader_file(include_path, output, false))
            goto error;

         /* After including a file, use line directive
          * to pull it back to current file. */
         push_line = 1;
      }
      else if (!strncmp("#endif", line, STRLEN_CONST("#endif")) ||
               !strncmp("#pragma", line, STRLEN_CONST("#pragma")))
      {
         /* #line seems to be ignored if preprocessor tests fail,
          * so we should reapply #line after each #endif.
          * Add extra offset here since we're setting #line
          * for the line after this one.
          */
         push_line = 2;
         if (!string_list_append(output, line, attr))
            goto error;
      }
      else
         if (!string_list_append(output, line, attr))
            goto error;

      if (push_line != 0)
      {
         snprintf(tmp, sizeof(tmp), "#line %u \"%s\"",
               (unsigned)(i + push_line), basename);
         if (!string_list_append(output, tmp, attr))
            goto error;
      }
   }

   string_list_free(lines);

   return true;

error:

   if (lines)
      string_list_free(lines);

   return false;
}