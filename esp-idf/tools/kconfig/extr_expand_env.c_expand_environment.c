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
 int MAX_LEN ; 
 scalar_t__ allowed_env_var_name (char const) ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 char* calloc (int,size_t) ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  free (char*) ; 
 char* getenv (char*) ; 
 char* malloc (int) ; 
 int /*<<< orphan*/  printf (char*,char const*,int,...) ; 
 int /*<<< orphan*/  strcpy (char*,char const*) ; 
 int strlen (char const*) ; 
 int /*<<< orphan*/  strncpy (char*,char const*,size_t) ; 

char *expand_environment(const char *input, const char *src_name, int src_line_no)
{
  char *result = malloc(MAX_LEN);

  char *out = result;
  const char *in = input;

  while (*in != '\0') {
    // check for buffer overflow
    if (out >= result + MAX_LEN - 1) {
      goto too_long;
    }

    if (*in != '$') {
      // not part of an environment variable name, copy directly
      *out++ = *in++;
      continue;
    }

    // *in points to start of an environment variable reference
    in++;
    const char *env_start = in;
    while (allowed_env_var_name(*in)) { // scan to the end of the name
      in++;
    }
    size_t env_len = in - env_start;

    // make a buffer to hold the environment variable name
    //
    // strndup is not available on mingw32, apparently.
    char *env_name = calloc(1, env_len + 1);
    assert(env_name != NULL);
    strncpy(env_name, env_start, env_len);

    const char *value = getenv(env_name);
    if (value == NULL || strlen(value) == 0) {
      printf("%s:%d: undefined environment variable \"%s\"\n",
             src_name, src_line_no, env_name);
      exit(1);
    }
    free(env_name);
    if (out + strlen(value) >= result + MAX_LEN - 1) {
      goto too_long;
    }
    strcpy(out, value); // append the value to the result (range checked in previous statement)
    out += strlen(value);
  }

  *out = '\0'; // null terminate the result string

  return result;

too_long:
  printf("%s:%d: Expansion is longer than %d bytes\n",
         src_name, src_line_no, MAX_LEN);
  free(result);
  exit(1);
}