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
 scalar_t__ ntags ; 
 int /*<<< orphan*/  putc_code (int /*<<< orphan*/ *,char) ; 
 int /*<<< orphan*/  putl_code (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  unionized ; 

__attribute__((used)) static void
output_stype(FILE * fp)
{
    if (!unionized && ntags == 0)
    {
	putc_code(fp, '\n');
	putl_code(fp, "#if "
		  "! defined(YYSTYPE) && "
		  "! defined(YYSTYPE_IS_DECLARED)\n");
	putl_code(fp, "/* Default: YYSTYPE is the semantic value type. */\n");
	putl_code(fp, "typedef int YYSTYPE;\n");
	putl_code(fp, "# define YYSTYPE_IS_DECLARED 1\n");
	putl_code(fp, "#endif\n");
    }
}