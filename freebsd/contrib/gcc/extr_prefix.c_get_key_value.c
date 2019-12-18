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
 char* concat (char*,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (char*) ; 
 char* getenv (char*) ; 
 char* lookup_key (char*) ; 
 char* std_prefix ; 

__attribute__((used)) static const char *
get_key_value (char *key)
{
  const char *prefix = 0;
  char *temp = 0;

#if defined(_WIN32) && defined(ENABLE_WIN32_REGISTRY)
  prefix = lookup_key (key);
#endif

  if (prefix == 0)
    prefix = getenv (temp = concat (key, "_ROOT", NULL));

  if (prefix == 0)
    prefix = std_prefix;

  if (temp)
    free (temp);

  return prefix;
}