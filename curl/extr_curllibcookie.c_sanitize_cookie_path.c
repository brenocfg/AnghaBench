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
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  memmove (void*,void const*,size_t) ; 
 char* strdup (char const*) ; 
 size_t strlen (char*) ; 

__attribute__((used)) static char *sanitize_cookie_path(const char *cookie_path)
{
  size_t len;
  char *new_path = strdup(cookie_path);
  if(!new_path)
    return NULL;

  /* some stupid site sends path attribute with '"'. */
  len = strlen(new_path);
  if(new_path[0] == '\"') {
    memmove((void *)new_path, (const void *)(new_path + 1), len);
    len--;
  }
  if(len && (new_path[len - 1] == '\"')) {
    new_path[len - 1] = 0x0;
    len--;
  }

  /* RFC6265 5.2.4 The Path Attribute */
  if(new_path[0] != '/') {
    /* Let cookie-path be the default-path. */
    free(new_path);
    new_path = strdup("/");
    return new_path;
  }

  /* convert /hoge/ to /hoge */
  if(len && new_path[len - 1] == '/') {
    new_path[len - 1] = 0x0;
  }

  return new_path;
}