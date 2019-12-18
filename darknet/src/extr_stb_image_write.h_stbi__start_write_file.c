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
typedef  int /*<<< orphan*/  stbi__write_context ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/ * fopen (char const*,char*) ; 
 scalar_t__ fopen_s (int /*<<< orphan*/ **,char const*,char*) ; 
 int /*<<< orphan*/  stbi__start_write_callbacks (int /*<<< orphan*/ *,int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  stbi__stdio_write ; 

__attribute__((used)) static int stbi__start_write_file(stbi__write_context *s, const char *filename)
{
   FILE *f;
#ifdef STBI_MSC_SECURE_CRT
   if (fopen_s(&f, filename, "wb"))
      f = NULL;
#else
   f = fopen(filename, "wb");
#endif
   stbi__start_write_callbacks(s, stbi__stdio_write, (void *) f);
   return f != NULL;
}