#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  codepointLocationColumn; int /*<<< orphan*/  tokenLocationColumn; int /*<<< orphan*/  codepointLocationLine; int /*<<< orphan*/  tokenLocationLine; int /*<<< orphan*/  codepointLocationByte; int /*<<< orphan*/  tokenLocationByte; int /*<<< orphan*/  token; } ;
typedef  int /*<<< orphan*/  Symbol ;
typedef  TYPE_1__* JSON_Parser ;

/* Variables and functions */

__attribute__((used)) static void JSON_Parser_StartToken(JSON_Parser parser, Symbol token)
{
   parser->token               = token;
   parser->tokenLocationByte   = parser->codepointLocationByte;
   parser->tokenLocationLine   = parser->codepointLocationLine;
   parser->tokenLocationColumn = parser->codepointLocationColumn;
}