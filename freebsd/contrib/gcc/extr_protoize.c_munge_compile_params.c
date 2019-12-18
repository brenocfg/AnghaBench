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
struct stat {int /*<<< orphan*/  st_mode; } ;

/* Variables and functions */
 char* HOST_BIT_BUCKET ; 
 scalar_t__ ISSPACE (unsigned char const) ; 
 int /*<<< orphan*/  S_ISDIR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  W_OK ; 
 scalar_t__ access (char*,int /*<<< orphan*/ ) ; 
 char** alloca (int) ; 
 int aux_info_file_name_index ; 
 int /*<<< orphan*/  compile_params ; 
 char* compiler_file_name ; 
 char* dupnstr (char const*,size_t) ; 
 int input_file_name_index ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,char const**,int) ; 
 scalar_t__ stat (char*,struct stat*) ; 
 int strlen (char const*) ; 
 int /*<<< orphan*/  xmalloc (int) ; 

__attribute__((used)) static void
munge_compile_params (const char *params_list)
{
  /* Build up the contents in a temporary vector
     that is so big that to has to be big enough.  */
  const char **temp_params
    = alloca ((strlen (params_list) + 8) * sizeof (char *));
  int param_count = 0;
  const char *param;
  struct stat st;

  temp_params[param_count++] = compiler_file_name;
  for (;;)
    {
      while (ISSPACE ((const unsigned char)*params_list))
	params_list++;
      if (!*params_list)
	break;
      param = params_list;
      while (*params_list && !ISSPACE ((const unsigned char)*params_list))
	params_list++;
      if (param[0] != '-')
	temp_params[param_count++]
	  = dupnstr (param, (size_t) (params_list - param));
      else
	{
	  switch (param[1])
	    {
	    case 'g':
	    case 'O':
	    case 'S':
	    case 'c':
	      break;		/* Don't copy these.  */
	    case 'o':
	      while (ISSPACE ((const unsigned char)*params_list))
		params_list++;
	      while (*params_list
		     && !ISSPACE ((const unsigned char)*params_list))
		params_list++;
	      break;
	    default:
	      temp_params[param_count++]
		= dupnstr (param, (size_t) (params_list - param));
	    }
	}
      if (!*params_list)
	break;
    }
  temp_params[param_count++] = "-aux-info";

  /* Leave room for the aux-info file name argument.  */
  aux_info_file_name_index = param_count;
  temp_params[param_count++] = NULL;

  temp_params[param_count++] = "-S";
  temp_params[param_count++] = "-o";

  if ((stat (HOST_BIT_BUCKET, &st) == 0)
      && (!S_ISDIR (st.st_mode))
      && (access (HOST_BIT_BUCKET, W_OK) == 0))
    temp_params[param_count++] = HOST_BIT_BUCKET;
  else
    /* FIXME: This is hardly likely to be right, if HOST_BIT_BUCKET is not
       writable.  But until this is rejigged to use make_temp_file(), this
       is the best we can do.  */
    temp_params[param_count++] = "/dev/null";

  /* Leave room for the input file name argument.  */
  input_file_name_index = param_count;
  temp_params[param_count++] = NULL;
  /* Terminate the list.  */
  temp_params[param_count++] = NULL;

  /* Make a copy of the compile_params in heap space.  */

  compile_params = xmalloc (sizeof (char *) * (param_count+1));
  memcpy (compile_params, temp_params, sizeof (char *) * param_count);
}