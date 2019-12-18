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
typedef  int /*<<< orphan*/  spvc_compiler ;

/* Variables and functions */
 int /*<<< orphan*/  SPVC_CHECKED_CALL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*,char const*) ; 
 int /*<<< orphan*/  spvc_compiler_compile (int /*<<< orphan*/ ,char const**) ; 

__attribute__((used)) static void compile(spvc_compiler compiler, const char *tag)
{
	const char *result = NULL;
	SPVC_CHECKED_CALL(spvc_compiler_compile(compiler, &result));
	printf("\n%s\n=======\n", tag);
	printf("%s\n=======\n", result);
}