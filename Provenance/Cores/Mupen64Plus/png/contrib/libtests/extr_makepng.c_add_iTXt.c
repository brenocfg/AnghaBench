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
typedef  int /*<<< orphan*/  png_const_charp ;
typedef  int /*<<< orphan*/ * png_charp ;
typedef  int /*<<< orphan*/  chunk_insert ;

/* Variables and functions */
 int /*<<< orphan*/  insert_iTXt ; 
 int /*<<< orphan*/ * make_insert (char*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/ * strstash (char const*) ; 
 int /*<<< orphan*/ * strstash_list (int /*<<< orphan*/  const*) ; 

__attribute__((used)) static chunk_insert *
add_iTXt(const char *key, const char *language, const char *language_key,
      const png_const_charp *text)
{
   static char what[5] = { 105, 84, 88, 116, 0 };
   png_charp parameter_list[5];

   parameter_list[0] = strstash(key);
   parameter_list[1] = strstash(language);
   parameter_list[2] = strstash(language_key);
   parameter_list[3] = strstash_list(text);
   parameter_list[4] = NULL;

   return make_insert(what, insert_iTXt, 4, parameter_list);
}