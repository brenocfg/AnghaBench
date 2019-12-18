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
 int /*<<< orphan*/  XFREE (char*) ; 
 int /*<<< orphan*/  memset (char*,int /*<<< orphan*/ ,size_t) ; 
 int strlen (char const*) ; 
 int /*<<< orphan*/  strncat (char*,char const*,size_t) ; 
 int /*<<< orphan*/  strncpy (char*,char const*,size_t) ; 
 char* strstr (char const*,char const*) ; 
 scalar_t__ xmalloc (size_t) ; 

__attribute__((used)) static char *
sun_strsub(const char *src, const char *str, const char *sub)
{

  char *retval = NULL, *str_start, *str_end, *src_end;
  size_t total_size, first_half, second_half, sub_size;

  /* assign pointers to the start and end of str */
  if ((str_start = strstr(src, str)) == NULL) {
    return retval;
  }
  str_end = (strlen(str) - 1) + str_start;

  /* assign to the end of the src. */
  src_end = (strlen(src) - 1) + (char*)src;

  /* size from the beginning of src to the start of str */
  first_half = (size_t)(str_start - src);

  /* size from the end of str to the end of src */
  second_half = (size_t)(src_end - str_end);

  sub_size = strlen(sub);

  total_size = (first_half + sub_size + second_half + 1);

  retval = (char*)xmalloc(total_size);
  memset(retval, 0, total_size);

  /*
   * Put together the string such that the first half is copied
   * followed the sub and second half.
   *
   * We use strncpy instead of xstrlcpy because we are intentionally
   * causing truncation and we don't want this to cause errors in the
   * log.
   */
  (void)strncpy(retval, src, first_half);
  (void)strncat(retval, sub, sub_size);
  (void)strncat(retval, str_end + 1, second_half);

  if (strstr(retval, str) != NULL) {
    /*
     * If there is another occurrences of str call this function
     * recursively.
     */
    char* tmp;
    if ((tmp = sun_strsub(retval, str, sub)) != NULL) {
      XFREE(retval);
      retval = tmp;
    }
  }
  return retval;
}