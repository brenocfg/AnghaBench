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
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int counter ; 
 int /*<<< orphan*/  emit_alias (int /*<<< orphan*/ *,char const*,char const* const,char const*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ *,char*,char const*,int) ; 

__attribute__((used)) static void emit_encoding (FILE* out1, FILE* out2, const char* tag, const char* const* names, size_t n, const char* c_name)
{
  fprintf(out2,"  (int)(long)&((struct stringpool2_t *)0)->stringpool_%s_%u,\n",tag,counter);
  for (; n > 0; names++, n--)
    emit_alias(out1, tag, *names, c_name);
}