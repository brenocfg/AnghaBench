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
typedef  int /*<<< orphan*/  expressionS ;

/* Variables and functions */
 int /*<<< orphan*/  assemble_tokens (int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int,int) ; 
 int /*<<< orphan*/  emit_uldXu (int /*<<< orphan*/  const*,int,void const*) ; 
 int /*<<< orphan*/ * sextX_op ; 

__attribute__((used)) static void
emit_uldX (const expressionS *tok,
	   int ntok,
	   const void * vlgsize)
{
  emit_uldXu (tok, ntok, vlgsize);
  assemble_tokens (sextX_op[(long) vlgsize], tok, 1, 1);
}