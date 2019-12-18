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
typedef  int /*<<< orphan*/  tree ;

/* Variables and functions */
 int /*<<< orphan*/  ASM_FORMAT_PRIVATE_NAME (char*,char const*,int /*<<< orphan*/ ) ; 
 char* ASTRDUP (char const*) ; 
 int /*<<< orphan*/  get_identifier (char*) ; 
 int /*<<< orphan*/  remove_suffix (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strlen (char*) ; 
 int /*<<< orphan*/  tmp_var_id_num ; 

tree
create_tmp_var_name (const char *prefix)
{
  char *tmp_name;

  if (prefix)
    {
      char *preftmp = ASTRDUP (prefix);

      remove_suffix (preftmp, strlen (preftmp));
      prefix = preftmp;
    }

  ASM_FORMAT_PRIVATE_NAME (tmp_name, prefix ? prefix : "T", tmp_var_id_num++);
  return get_identifier (tmp_name);
}