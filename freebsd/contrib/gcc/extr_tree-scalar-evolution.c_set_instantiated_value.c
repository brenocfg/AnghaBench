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
typedef  void* tree ;
struct scev_info_str {void* chrec; void* var; } ;
typedef  int /*<<< orphan*/  htab_t ;
typedef  scalar_t__ PTR ;

/* Variables and functions */
 int /*<<< orphan*/  INSERT ; 
 scalar_t__* htab_find_slot (int /*<<< orphan*/ ,struct scev_info_str*,int /*<<< orphan*/ ) ; 
 scalar_t__ new_scev_info_str (void*) ; 

__attribute__((used)) static void
set_instantiated_value (htab_t cache, tree version, tree val)
{
  struct scev_info_str *info, pattern;
  PTR *slot;
  
  pattern.var = version;
  slot = htab_find_slot (cache, &pattern, INSERT);

  if (!*slot)
    *slot = new_scev_info_str (version);
  info = (struct scev_info_str *) *slot;
  info->chrec = val;
}