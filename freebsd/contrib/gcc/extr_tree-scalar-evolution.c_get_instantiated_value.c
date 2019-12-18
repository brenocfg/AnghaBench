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
struct scev_info_str {int /*<<< orphan*/  chrec; int /*<<< orphan*/  var; } ;
typedef  int /*<<< orphan*/  htab_t ;

/* Variables and functions */
 int /*<<< orphan*/  NULL_TREE ; 
 scalar_t__ htab_find (int /*<<< orphan*/ ,struct scev_info_str*) ; 

__attribute__((used)) static tree
get_instantiated_value (htab_t cache, tree version)
{
  struct scev_info_str *info, pattern;
  
  pattern.var = version;
  info = (struct scev_info_str *) htab_find (cache, &pattern);

  if (info)
    return info->chrec;
  else
    return NULL_TREE;
}