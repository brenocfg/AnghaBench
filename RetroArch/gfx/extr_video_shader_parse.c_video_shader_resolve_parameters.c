#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
struct video_shader_parameter {unsigned int pass; char* id; char* desc; float minimum; float maximum; float step; int /*<<< orphan*/  initial; int /*<<< orphan*/  current; } ;
struct video_shader {scalar_t__ num_parameters; unsigned int passes; struct video_shader_parameter* parameters; TYPE_2__* pass; } ;
struct string_list {size_t size; TYPE_3__* elems; } ;
typedef  scalar_t__ int64_t ;
typedef  int /*<<< orphan*/  config_file_t ;
struct TYPE_6__ {char* data; } ;
struct TYPE_4__ {char* path; } ;
struct TYPE_5__ {TYPE_1__ source; } ;

/* Variables and functions */
 scalar_t__ ARRAY_SIZE (struct video_shader_parameter*) ; 
 int /*<<< orphan*/  RARCH_LOG (char*,char*,char*,int /*<<< orphan*/ ,float,float,float,unsigned int) ; 
 int /*<<< orphan*/  STRLEN_CONST (char*) ; 
 int /*<<< orphan*/  filestream_read_file (char const*,void**,scalar_t__*) ; 
 int /*<<< orphan*/  free (void*) ; 
 int /*<<< orphan*/  path_get_extension (char const*) ; 
 int /*<<< orphan*/  path_is_valid (char const*) ; 
 scalar_t__ slang_preprocess_parse_parameters (char const*,struct video_shader*) ; 
 int sscanf (char const*,char*,char*,char*,int /*<<< orphan*/ *,float*,float*,float*) ; 
 scalar_t__ string_is_empty (char const*) ; 
 scalar_t__ string_is_equal (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  string_list_free (struct string_list*) ; 
 struct string_list* string_split (char const*,char*) ; 
 scalar_t__ strncmp (char*,char const*,int /*<<< orphan*/ ) ; 
 int video_shader_resolve_current_parameters (int /*<<< orphan*/ *,struct video_shader*) ; 

bool video_shader_resolve_parameters(config_file_t *conf,
      struct video_shader *shader)
{
   unsigned i;
   struct video_shader_parameter *param = &shader->parameters[0];

   shader->num_parameters = 0;

   /* Find all parameters in our shaders. */

   for (i = 0; i < shader->passes; i++)
   {
      const char *path          = shader->pass[i].source.path;
      uint8_t *buf              = NULL;
      int64_t buf_len           = 0;
      struct string_list *lines = NULL;
      size_t line_index         = 0;

      if (string_is_empty(path))
         continue;

      if (!path_is_valid(path))
         continue;

#if defined(HAVE_SLANG) && defined(HAVE_SPIRV_CROSS)
      /* First try to use the more robust slang
       * implementation to support #includes. */
      /* FIXME: The check for slang can be removed
       * if it's sufficiently tested for
       * GLSL/Cg as well, it should be the same implementation. */
      if (string_is_equal(path_get_extension(path), "slang") &&
            slang_preprocess_parse_parameters(path, shader))
         continue;

      /* If that doesn't work, fallback to the old path.
       * Ideally, we'd get rid of this path sooner or later. */
#endif

      /* Read file contents */
      if (!filestream_read_file(path, (void**)&buf, &buf_len))
         continue;

      /* Split into lines */
      if (buf_len > 0)
         lines = string_split((const char*)buf, "\n");

      /* Buffer is no longer required - clean up */
      if ((void*)buf)
         free((void*)buf);

      if (!lines)
         continue;

      /* even though the pass is set in the loop too, not all passes have parameters */
      param->pass = i;

      while ((shader->num_parameters < ARRAY_SIZE(shader->parameters)) &&
             (line_index < lines->size))
      {
         int ret;
         const char *line = lines->elems[line_index].data;
         line_index++;

         /* Check if this is a '#pragma parameter' line */
         if (strncmp("#pragma parameter", line,
                  STRLEN_CONST("#pragma parameter")))
            continue;

         /* Parse line */
         ret = sscanf(line, "#pragma parameter %63s \"%63[^\"]\" %f %f %f %f",
               param->id,        param->desc,    &param->initial,
               &param->minimum, &param->maximum, &param->step);

         if (ret < 5)
            continue;

         param->id[63]   = '\0';
         param->desc[63] = '\0';

         if (ret == 5)
            param->step = 0.1f * (param->maximum - param->minimum);

         param->pass = i;

         RARCH_LOG("Found #pragma parameter %s (%s) %f %f %f %f in pass %d\n",
               param->desc,    param->id,      param->initial,
               param->minimum, param->maximum, param->step, param->pass);
         param->current = param->initial;

         shader->num_parameters++;
         param++;
      }

      string_list_free(lines);
   }

   return video_shader_resolve_current_parameters(conf, shader);
}